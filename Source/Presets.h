#pragma once

#include <utility>
#include <vector>

namespace smkp
{
struct Preset
{
    const char* name;
    std::vector<std::pair<const char*, float>> values; // valori "veri" (non normalizzati)
};

// Ogni preset parte dai default e cambia solo quello che elenca.
// nsNoise: 0 White, 1 Pink, 2 Brown, 3 Blue, 4 Violet, 5 Grey, 6 Breath, 7 Silk, 8 Smoke, 9 Tape, 10 Custom
inline const std::vector<Preset>& presets()
{
    static const std::vector<Preset> list = {
        { "Sibilants - Pink",          {} },
        { "Sibilants - Silk Air",      { { "nsNoise", 7.0f }, { "nsStart", 4000.0f }, { "nsEnd", 16000.0f }, { "nsAmount", 70.0f } } },
        { "Sibilants - Dark Smoke",    { { "nsNoise", 8.0f }, { "nsStart", 2500.0f }, { "nsEnd", 12000.0f }, { "nsAmount", 75.0f }, { "nsDetail", 35.0f } } },
        { "Sibilants - Surgical",      { { "nsDetail", 85.0f }, { "nsSpeed", 5.0f }, { "nsAmount", 80.0f }, { "nsSlope", 48.0f } } },
        { "S Only - Grey",             { { "nsNoise", 5.0f }, { "detF", 0.0f }, { "detC", 0.0f }, { "nsStart", 4500.0f } } },
        { "F and V - Breath",          { { "nsNoise", 6.0f }, { "detS", 0.0f }, { "detC", 0.0f }, { "nsStart", 1500.0f }, { "nsEnd", 10000.0f }, { "sensF", 60.0f } } },
        { "Full Signal - Air Balance", { { "nsFull", 1.0f }, { "nsNoise", 1.0f }, { "nsStart", 5000.0f }, { "nsEnd", 18000.0f }, { "nsAmount", 35.0f }, { "nsSpeed", 120.0f }, { "nsDetail", 30.0f } } },
        { "Full Signal - Tape Top",    { { "nsFull", 1.0f }, { "nsNoise", 9.0f }, { "nsStart", 3000.0f }, { "nsEnd", 20000.0f }, { "nsAmount", 40.0f }, { "nsSpeed", 80.0f } } },
        { "Full Signal - Pink Mix",    { { "nsFull", 1.0f }, { "nsNoise", 1.0f }, { "nsStart", 60.0f }, { "nsEnd", 16000.0f }, { "nsAmount", 25.0f }, { "nsSpeed", 250.0f }, { "nsDetail", 20.0f }, { "nsSlope", 12.0f } } },
        { "Live - Sibilants",          { { "res", 0.0f } } },
    };
    return list;
}
}
