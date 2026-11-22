// Strumento di prova (solo Linux): fa suonare N-Shaper su un file e salva l'interfaccia vera in PNG
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include "../Source/PluginProcessor.h"
#include "../Source/PluginEditor.h"
#include <fstream>

using namespace juce;

int main (int argc, char** argv)
{
    ScopedJuceInitialiser_GUI init;
    if (argc < 4) { printf ("uso: NShaperSnap audio.f32 stopSec outdir [noise] [full]\n"); return 1; }
    const File outDir (argv[3]);
    outDir.createDirectory();

    std::vector<float> x;
    {
        std::ifstream f (argv[1], std::ios::binary);
        float v; while (f.read ((char*) &v, 4)) x.push_back (v);
    }
    const double stopSec = atof (argv[2]);

    // rumore personalizzato di prova: fruscio con una gobba a 5 kHz, scritto in WAV e caricato dal percorso normale
    const File nFile = outDir.getChildFile ("fruscio.wav");
    {
        AudioBuffer<float> b (2, 48000 * 3);
        Random r (7);
        IIRFilter bp1, bp2;
        bp1.setCoefficients (IIRCoefficients::makeBandPass (48000.0, 5000.0, 1.2));
        bp2.setCoefficients (IIRCoefficients::makeBandPass (48000.0, 5000.0, 1.2));
        for (int i = 0; i < b.getNumSamples(); ++i)
        {
            const float w = r.nextFloat() - 0.5f;
            b.setSample (0, i, 0.1f * w + 0.6f * bp1.processSingleSampleRaw (w));
        }
        b.copyFrom (1, 0, b, 0, 0, b.getNumSamples());
        WavAudioFormat wav;
        nFile.deleteFile();
        std::unique_ptr<AudioFormatWriter> wr (wav.createWriterFor (new FileOutputStream (nFile), 48000, 2, 24, {}, 0));
        wr->writeFromAudioSampleBuffer (b, 0, b.getNumSamples());
    }

    NShaperProcessor proc;
    proc.prepareToPlay (48000.0, 512);
    auto set = [&] (const char* id, float v) { auto* p = proc.apvts.getParameter (id); p->setValueNotifyingHost (p->convertTo0to1 (v)); };
    printf ("rumore %s\n", proc.loadNoise (nFile) ? "ok" : "FAIL");
    set ("nsNoise", argc > 4 ? (float) atoi (argv[4]) : 10.0f);
    set ("nsAmount", 90.0f);
    if (argc > 5) set ("nsFull", (float) atoi (argv[5]));

    AudioBuffer<float> buf (2, 512);
    MidiBuffer midi;
    const int stop = (int) (stopSec * 48000.0);
    for (int i = 0; i + 512 <= stop && i + 512 <= (int) x.size(); i += 512)
    {
        for (int c = 0; c < 2; ++c) buf.copyFrom (c, 0, x.data() + i, 512);
        proc.processBlock (buf, midi);
    }

    const char* pages[] = { "nshaper", "detect" };
    for (int skin = 0; skin < (int) ui::skins().size(); ++skin)
        for (int pg = 0; pg < 2; ++pg)
        {
            if (skin > 0 && pg > 0 && skin != 4) continue;
            proc.uiSkin = skin;
            proc.uiPage = pg;
            std::unique_ptr<AudioProcessorEditor> ed (proc.createEditor());
            MessageManager::getInstance()->runDispatchLoopUntil (400);
            auto img = ed->createComponentSnapshot (ed->getLocalBounds(), true, 2.0f);
            const File f = outDir.getChildFile (String ("NSHAPER-") + ui::skins()[(size_t) skin].name + "-" + pages[pg] + ".png");
            f.deleteFile();
            FileOutputStream os (f);
            PNGImageFormat().writeImageToStream (img, os);
            printf ("%s\n", f.getFullPathName().toRawUTF8());
        }
    return 0;
}
