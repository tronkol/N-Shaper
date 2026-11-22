#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Presets.h"

using namespace juce;

namespace
{
String pct (float v, int)  { return String (juce::roundToInt (v)) + " %"; }
String ms (float v, int)   { return v < 10.0f ? String (v, 1) + " ms" : String (juce::roundToInt (v)) + " ms"; }
String db (float v, int)   { return (v > 0.05f ? "+" : "") + String (v, 1) + " dB"; }
String dbo (float v, int)  { return String (juce::roundToInt (v)) + " dB/oct"; }
String hz (float v, int)   { return v < 1000.0f ? String (juce::roundToInt (v)) + " Hz" : String (v / 1000.0f, v < 10000.0f ? 2 : 1) + " kHz"; }

NormalisableRange<float> skewed (float lo, float hi, float centre)
{
    NormalisableRange<float> r (lo, hi);
    r.setSkewForCentre (centre);
    return r;
}
}

AudioProcessorValueTreeState::ParameterLayout NShaperProcessor::createLayout()
{
    using F = AudioParameterFloat;
    using B = AudioParameterBool;
    using A = AudioParameterFloatAttributes;
    std::vector<std::unique_ptr<RangedAudioParameter>> p;

    auto fl = [&p] (const char* id, const char* name, NormalisableRange<float> r, float def, String (*fmt) (float, int))
    {
        p.push_back (std::make_unique<F> (ParameterID { id, 1 }, name, r, def, A().withStringFromValueFunction (fmt)));
    };

    // N-SHAPER
    p.push_back (std::make_unique<AudioParameterChoice> (ParameterID { "nsFull", 1 }, "Target", StringArray { "Sibilants", "Full Signal" }, 0));
    {
        StringArray noises;
        for (int i = 0; i < smk::kNumNoises; ++i)
        {
            const String n (smk::noiseName (i));
            noises.add (n.substring (0, 1) + n.substring (1).toLowerCase());
        }
        noises.add ("Custom");
        p.push_back (std::make_unique<AudioParameterChoice> (ParameterID { "nsNoise", 1 }, "Noise", noises, 1));
    }
    fl ("nsStart",   "Start",   skewed (20.0f, 20000.0f, 1000.0f), 3000.0f, hz);
    fl ("nsEnd",     "End",     skewed (20.0f, 20000.0f, 1000.0f), 12000.0f, hz);
    fl ("nsSlope",   "Slope",   skewed (6.0f, 96.0f, 24.0f), 24.0f, dbo);
    fl ("nsAmount",  "Amount",  { 0.0f, 100.0f, 0.1f }, 60.0f, pct);
    fl ("nsMakeup",  "Makeup",  { -24.0f, 24.0f, 0.1f }, 0.0f, db);
    fl ("nsSpeed",   "Speed",   skewed (1.0f, 300.0f, 20.0f), 15.0f, ms);
    fl ("nsDetail",  "Detail",  { 0.0f, 100.0f, 0.1f }, 50.0f, pct);
    fl ("nsDynamic", "Dynamic", { 0.0f, 100.0f, 0.1f }, 50.0f, pct);
    p.push_back (std::make_unique<AudioParameterChoice> (ParameterID { "res", 1 }, "Resolution",
                                                         StringArray { "LIVE (zero latency)", "513 bands", "1025 bands", "2049 bands", "4097 bands", "8193 bands" }, 2));

    // DETECT
    p.push_back (std::make_unique<B> (ParameterID { "detS", 1 }, "Detect S/Z/SH", true));
    p.push_back (std::make_unique<B> (ParameterID { "detF", 1 }, "Detect F/V", true));
    p.push_back (std::make_unique<B> (ParameterID { "detC", 1 }, "Detect CH/J", true));
    fl ("sensS", "Sens S",  { 0.0f, 100.0f, 0.1f }, 50.0f, pct);
    fl ("sensF", "Sens F",  { 0.0f, 100.0f, 0.1f }, 50.0f, pct);
    fl ("sensC", "Sens C",  { 0.0f, 100.0f, 0.1f }, 50.0f, pct);
    fl ("hold",  "Hold",    skewed (5.0f, 250.0f, 40.0f), 40.0f, ms);
    fl ("guard", "Vowel Guard", { 0.0f, 100.0f, 0.1f }, 60.0f, pct);

    // piede
    fl ("mix",    "Mix",    { 0.0f, 100.0f, 0.1f }, 100.0f, pct);
    fl ("output", "Output", { -24.0f, 24.0f, 0.1f }, 0.0f, db);
    p.push_back (std::make_unique<B> (ParameterID { "delta", 1 },  "Delta", false));
    p.push_back (std::make_unique<B> (ParameterID { "listen", 1 }, "Consonants Only", false));

    return { p.begin(), p.end() };
}

//==============================================================================
NShaperProcessor::NShaperProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "NSHAPER", createLayout())
{
    formats.registerBasicFormats();
    engine = std::make_unique<smk::Engine> (visData);
    engine->prepare (48000.0, currentRes());
    apvts.addParameterListener ("res", this);
}

NShaperProcessor::~NShaperProcessor()
{
    apvts.removeParameterListener ("res", this);
    cancelPendingUpdate();
    alive.reset();
}

void NShaperProcessor::handleAsyncUpdate()
{
    const int r = currentRes();
    if (engine != nullptr && engine->resolution() == r) return;
    auto e = std::make_unique<smk::Engine> (visData);
    e->prepare (currentSR, r);
    {
        const ScopedLock sl (engineLock);
        std::swap (engine, e);
    }
    setLatencySamples (engine->latency()); // l'host ricalcola la compensazione
}

bool NShaperProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto in = layouts.getMainInputChannelSet(), out = layouts.getMainOutputChannelSet();
    if (in != out) return false;
    return out == AudioChannelSet::mono() || out == AudioChannelSet::stereo();
}

void NShaperProcessor::prepareToPlay (double sampleRate, int)
{
    currentSR = sampleRate;
    {
        auto e = std::make_unique<smk::Engine> (visData);
        e->prepare (sampleRate, currentRes());
        const ScopedLock sl (engineLock);
        engine = std::move (e);
    }
    setLatencySamples (engine->latency());
    outGain.reset (sampleRate, 0.05);
    outGain.setCurrentAndTargetValue (Decibels::decibelsToGain (apvts.getRawParameterValue ("output")->load()));
    // il rumore personalizzato e' in Hz: non dipende dal sample rate, niente da ricostruire
}

void NShaperProcessor::readParams (smk::Params& p)
{
    auto v = [this] (const char* id) { return apvts.getRawParameterValue (id)->load(); };
    p.mix    = v ("mix") * 0.01f;
    p.delta  = v ("delta") > 0.5f;
    p.listen = v ("listen") > 0.5f;

    p.enS = v ("detS") > 0.5f; p.enF = v ("detF") > 0.5f; p.enC = v ("detC") > 0.5f;
    p.sensS = v ("sensS") * 0.01f; p.sensF = v ("sensF") * 0.01f; p.sensC = v ("sensC") * 0.01f;
    p.holdMs = v ("hold");
    p.guard  = v ("guard") * 0.01f;

    p.texOn      = false;
    p.nsOn       = true;
    p.nsFull     = v ("nsFull") > 0.5f;
    p.nsNoise    = (int) v ("nsNoise");
    p.nsStart    = v ("nsStart");
    p.nsEnd      = v ("nsEnd");
    p.nsSlope    = v ("nsSlope");
    p.nsAmount   = v ("nsAmount") * 0.01f;
    p.nsMakeupDb = v ("nsMakeup");
    p.nsSpeedMs  = v ("nsSpeed");
    p.nsDetail   = v ("nsDetail") * 0.01f;
    p.nsDynamic  = v ("nsDynamic") * 0.01f;
}

void NShaperProcessor::run (AudioBuffer<float>& buffer, bool bypass)
{
    ScopedNoDenormals noDenormals;
    const int nIn = getTotalNumInputChannels(), nOut = getTotalNumOutputChannels();
    for (int c = nIn; c < nOut; ++c) buffer.clear (c, 0, buffer.getNumSamples());

    smk::Params p;
    readParams (p);
    p.bypass = bypass;

    const int nc = jmin (2, buffer.getNumChannels());
    if (nc == 0) return;
    {
        const ScopedTryLock sl (engineLock);
        if (! sl.isLocked() || engine == nullptr)
        {
            buffer.clear(); // solo durante il cambio di risoluzione (un blocco)
            return;
        }
        engine->setParams (p);
        engine->setCustomNoise (currentNoise.load());
        engine->process (buffer.getArrayOfWritePointers(), nc, buffer.getNumSamples());
    }

    outGain.setTargetValue (bypass ? 1.0f : Decibels::decibelsToGain (apvts.getRawParameterValue ("output")->load()));
    if (outGain.isSmoothing() || std::abs (outGain.getTargetValue() - 1.0f) > 1.0e-6f)
    {
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            const float g = outGain.getNextValue();
            for (int c = 0; c < nc; ++c) buffer.getWritePointer (c)[i] *= g;
        }
    }
}

void NShaperProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer&)          { run (buffer, false); }
void NShaperProcessor::processBlockBypassed (AudioBuffer<float>& buffer, MidiBuffer&)  { run (buffer, true); }

//==============================================================================
// RUMORE PERSONALIZZATO: lo spettro medio del file diventa la forma bersaglio
bool NShaperProcessor::loadNoise (const File& file)
{
    std::unique_ptr<AudioFormatReader> reader (formats.createReaderFor (file));
    if (reader == nullptr || reader->lengthInSamples <= 0 || reader->sampleRate <= 0.0)
        return false;

    const int len = (int) jmin<int64> (reader->lengthInSamples, (int64) (reader->sampleRate * 180.0)); // max 3 minuti
    const int nch = (int) jmin<unsigned int> (2u, reader->numChannels);
    AudioBuffer<float> b (nch, len);
    reader->read (&b, 0, len, 0, true, nch > 1);
    std::vector<float> mono ((size_t) len, 0.0f);
    for (int c = 0; c < nch; ++c)
    {
        const float* src = b.getReadPointer (c);
        for (int i = 0; i < len; ++i) mono[(size_t) i] += src[i] / (float) nch;
    }

    auto n = std::make_unique<smk::CustomNoise> (smk::buildCustomNoise (mono.data(), len, reader->sampleRate));
    n->name = file.getFileName().toStdString();
    {
        const ScopedLock sl (noiseLock);
        noisePath = file.getFullPathName();
        currentNoise.store (n.get());
        noiseStore.push_back (std::move (n));
        while (noiseStore.size() > 8) noiseStore.erase (noiseStore.begin()); // l'audio ne usa al massimo uno per blocco
    }
    ++noiseVer;

    if (auto* prm = apvts.getParameter ("nsNoise"))
    {
        prm->beginChangeGesture();
        prm->setValueNotifyingHost (prm->convertTo0to1 ((float) smk::kCustomNoise));
        prm->endChangeGesture();
    }
    return true;
}

void NShaperProcessor::clearNoise()
{
    {
        const ScopedLock sl (noiseLock);
        noisePath = {};
        currentNoise.store (nullptr);
    }
    ++noiseVer;
}

//==============================================================================
int NShaperProcessor::getNumPrograms() { return (int) smkp::presets().size(); }

const String NShaperProcessor::getProgramName (int index)
{
    const auto& l = smkp::presets();
    return isPositiveAndBelow (index, (int) l.size()) ? String (l[(size_t) index].name) : String();
}

void NShaperProcessor::setCurrentProgram (int index) { applyPreset (index); }

void NShaperProcessor::applyPreset (int index)
{
    const auto& l = smkp::presets();
    if (! isPositiveAndBelow (index, (int) l.size())) return;
    currentPreset = index;

    // i preset non toccano ascolto, uscita e risoluzione
    static const StringArray keep { "delta", "listen", "output", "res" };
    for (auto* prm : getParameters())
        if (auto* r = dynamic_cast<RangedAudioParameter*> (prm))
        {
            if (keep.contains (r->getParameterID())) continue;
            r->setValueNotifyingHost (r->getDefaultValue());
        }

    for (const auto& kv : l[(size_t) index].values)
        if (auto* r = apvts.getParameter (kv.first))
            r->setValueNotifyingHost (r->convertTo0to1 (kv.second));
}

void NShaperProcessor::getStateInformation (MemoryBlock& destData)
{
    // copia dello stato + dati dell'interfaccia: nessuna scrittura nello stato condiviso
    // (Logic salva da un suo thread)
    auto state = apvts.copyState();
    {
        const ScopedLock sl (noiseLock);
        state.setProperty ("noisePath", noisePath, nullptr);
    }
    state.setProperty ("skin", uiSkin.load(), nullptr);
    state.setProperty ("uiPage", uiPage.load(), nullptr);
    if (auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void NShaperProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
        {
            const auto tree = ValueTree::fromXml (*xml);
            uiSkin = (int) tree.getProperty ("skin", 0);
            uiPage = (int) tree.getProperty ("uiPage", 0);
            const String path = tree.getProperty ("noisePath", String()).toString();
            apvts.replaceState (tree);
            if (path.isNotEmpty())
            {
                std::weak_ptr<bool> w = alive;
                MessageManager::callAsync ([this, w, path]
                {
                    if (w.expired()) return;
                    const File f (path);
                    if (! f.existsAsFile()) return;
                    // ricaricando il file la scelta del rumore resta quella salvata
                    const float keepNoise = apvts.getRawParameterValue ("nsNoise")->load();
                    loadNoise (f);
                    if (auto* prm = apvts.getParameter ("nsNoise"))
                        prm->setValueNotifyingHost (prm->convertTo0to1 (keepNoise));
                });
            }
        }
}

AudioProcessorEditor* NShaperProcessor::createEditor() { return new NShaperEditor (*this); }

AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new NShaperProcessor(); }
