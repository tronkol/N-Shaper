#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include "NShaperDSP.h"

class NShaperProcessor : public juce::AudioProcessor,
                         private juce::AudioProcessorValueTreeState::Listener,
                         private juce::AsyncUpdater
{
public:
    NShaperProcessor();
    ~NShaperProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlockBypassed (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override;
    int getCurrentProgram() override { return currentPreset; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // rumore personalizzato (solo dal thread dei messaggi)
    bool loadNoise (const juce::File& file);
    void clearNoise();
    const smk::CustomNoise* customNoise() const { return currentNoise.load(); }
    int noiseVersion() const { return noiseVer.load(); }

    void applyPreset (int index);

    smk::Vis& vis() { return visData; }
    int latencyMs() const { return (int) std::lround (1000.0 * getLatencySamples() / juce::jmax (1.0, currentSR)); }
    int bandsFor (int res) const { return smk::Engine::fftSizeFor (currentSR, res) / 2 + 1; }
    int latencyMsFor (int res) const { return (int) std::lround (1000.0 * smk::Engine::latencyFor (currentSR, res) / juce::jmax (1.0, currentSR)); }
    double sampleRate() const { return currentSR; }

    juce::AudioProcessorValueTreeState apvts;
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();

    // stato dell'interfaccia: salvato con il progetto, ma fuori dallo stato condiviso dei parametri
    std::atomic<int> uiSkin { 0 }, uiPage { 0 };

private:
    void readParams (smk::Params&);
    void run (juce::AudioBuffer<float>&, bool bypass);

    void parameterChanged (const juce::String&, float) override { triggerAsyncUpdate(); }
    void handleAsyncUpdate() override;   // cambio di risoluzione: nuovo motore costruito fuori dall'audio
    int currentRes() const { return (int) apvts.getRawParameterValue ("res")->load(); }

    smk::Vis visData;
    std::unique_ptr<smk::Engine> engine;
    juce::CriticalSection engineLock;   // l'audio lo prova senza aspettare
    double currentSR = 48000.0;
    int currentPreset = 0;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> outGain { 1.0f };

    juce::AudioFormatManager formats;
    std::atomic<const smk::CustomNoise*> currentNoise { nullptr };
    std::vector<std::unique_ptr<smk::CustomNoise>> noiseStore; // i vecchi restano vivi: l'audio puo' ancora usarli
    std::atomic<int> noiseVer { 0 };
    juce::CriticalSection noiseLock;
    juce::String noisePath;
    std::shared_ptr<bool> alive = std::make_shared<bool> (true);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NShaperProcessor)
};
