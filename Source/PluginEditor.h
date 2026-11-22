#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

namespace ui
{
// Una skin = solo colori. Ruoli come in ULTRAMEGASUPERMAXICHORUS, piu' quelli del display.
struct Palette
{
    const char* name;
    juce::Colour bg, band, text, strong, body, mark, arc, fill, onFill, field, accent, hot;
    juce::Colour specIn, specOut, gr, curve;
    std::array<juce::Colour, 3> cls; // S, F, C
};

const std::vector<Palette>& skins();
juce::Font font (float size, bool bold = false);
}

class FlatLook : public juce::LookAndFeel_V4
{
public:
    FlatLook();
    void setSkin (int index);
    int getSkin() const { return skin; }
    const ui::Palette& pal() const { return ui::skins()[(size_t) skin]; }

    void drawRotarySlider (juce::Graphics&, int x, int y, int width, int height,
                           float sliderPos, float startAngle, float endAngle, juce::Slider&) override;
    juce::Label* createSliderTextBox (juce::Slider&) override;
    void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour&, bool highlighted, bool down) override;
    void drawButtonText (juce::Graphics&, juce::TextButton&, bool highlighted, bool down) override;
    void drawComboBox (juce::Graphics&, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox&) override;
    void drawLinearSlider (juce::Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos,
                           float maxSliderPos, juce::Slider::SliderStyle, juce::Slider&) override;
    int getSliderThumbRadius (juce::Slider&) override { return 8; }
    juce::Font getComboBoxFont (juce::ComboBox&) override;
    juce::Font getPopupMenuFont() override;
    void positionComboBoxText (juce::ComboBox&, juce::Label&) override;

private:
    int skin = 0;
};

const ui::Palette& palOf (const juce::Component&);

//==============================================================================
// Storia del detector: cosa ha riconosciuto negli ultimi secondi
class DetectTimeline : public juce::Component, private juce::Timer
{
public:
    explicit DetectTimeline (NShaperProcessor&);
    void paint (juce::Graphics&) override;

private:
    void timerCallback() override;
    NShaperProcessor& proc;
    static constexpr int kCols = 600;
    struct Col { float s = 0, f = 0, c = 0, d = 0, lvl = 0; };
    std::array<Col, kCols> cols {};
    int head = 0;
    uint32_t readPos = 0;
};

// IN / GR / OUT nel piede
class Meters : public juce::Component, private juce::Timer
{
public:
    explicit Meters (NShaperProcessor&);
    void paint (juce::Graphics&) override;

private:
    void timerCallback() override;
    NShaperProcessor& proc;
    float in = -90.0f, out = -90.0f, gr = 0.0f, inPk = -90.0f, outPk = -90.0f;
    int inHold = 0, outHold = 0;
};

// N-SHAPER: spettro della banda, rumore bersaglio, correzione, bordi trascinabili
class NsView : public juce::Component, private juce::Timer
{
public:
    explicit NsView (NShaperProcessor&);
    void paint (juce::Graphics&) override;
    void mouseMove (const juce::MouseEvent&) override;
    void mouseDown (const juce::MouseEvent&) override;
    void mouseDrag (const juce::MouseEvent&) override;
    void mouseUp (const juce::MouseEvent&) override;

private:
    void timerCallback() override;
    float xOf (float hz) const;
    float hzOf (float x) const;
    int hitEdge (float x) const;
    NShaperProcessor& proc;
    static constexpr int P = smk::Vis::kPts;
    std::array<float, P> sS {}, sT {}, sG {};
    int drag = -1, hover = -1;
};

// N-SHAPER: livello della banda rispetto a FLOOR e intervento del momento
class NsMeter : public juce::Component, private juce::Timer
{
public:
    explicit NsMeter (NShaperProcessor&);
    void paint (juce::Graphics&) override;

private:
    void timerCallback() override;
    NShaperProcessor& proc;
    float level = -120.0f, ref = -60.0f, amt = 0.0f;
};

// Luci delle classi rilevate + latenza
class DetectLights : public juce::Component, private juce::Timer
{
public:
    explicit DetectLights (NShaperProcessor&);
    void paint (juce::Graphics&) override;

private:
    void timerCallback() override;
    NShaperProcessor& proc;
    std::array<float, 3> lv {};
};

//==============================================================================
class NShaperEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit NShaperEditor (NShaperProcessor&);
    ~NShaperEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    static constexpr int baseW = 422, baseH = 640;
    static constexpr int pageY = 86, pageH = 434;
    static constexpr double pageAnimMs = 600.0;

private:
    void timerCallback() override;

    struct Knob
    {
        juce::Slider slider;
        juce::Label  name;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> att;
    };
    struct Toggle
    {
        juce::TextButton button;
        std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> att;
    };

    class Content : public juce::Component
    {
    public:
        void paint (juce::Graphics&) override;
        float tabX = 16.0f; // barretta sotto la tab attiva
    };
    class Page : public juce::Component
    {
    public:
        explicit Page (int i) : index (i) {}
        void paint (juce::Graphics&) override;
        int index;
    };

    void setupKnob (Knob&, juce::Component& parent, const juce::String& paramId, const juce::String& label, const juce::String& tip, bool big = false);
    void setupToggle (Toggle&, juce::Component& parent, const juce::String& paramId, const juce::String& text, const juce::String& tip, const juce::String& kind = {});
    static void placeKnob (Knob&, juce::Rectangle<int> cell);
    void showPage (int page, bool animate);
    void applySkin (int index);
    void setParam (const char* id, float value);
    std::vector<Knob*> allKnobs();
    void chooseNoise();

    NShaperProcessor& proc;
    FlatLook look;
    Content content;
    juce::Component clip, strip;
    Page pNoise { 0 }, pDetect { 1 };

    DetectTimeline timeline;
    Meters meters;
    DetectLights lights;

    // N-SHAPER
    NsView nsView;
    juce::TextButton nsSibBtn { "SIBILANTS" }, nsFullBtn { "FULL SIGNAL" };
    juce::ComboBox nsNoiseBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> nsNoiseAtt;
    juce::TextButton noiseLoadBtn { "LOAD NOISE" }, noiseClearBtn { "X" };
    juce::Slider nsRange { juce::Slider::TwoValueHorizontal, juce::Slider::NoTextBox };
    juce::Label nsStartLbl, nsEndLbl;
    Knob nsSlope, nsAmount, nsMakeup, nsSpeed, nsDetail, nsDynamic;
    NsMeter nsMeter;
    juce::ComboBox resBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> resAtt;
    bool nsRangeDragging = false;
    // DETECT
    Knob sensS, sensF, sensC, hold, guard;
    Toggle detS, detF, detC;
    // piede
    Knob mix, output;
    Toggle delta, listen;

    static constexpr int kPages = 2;
    static constexpr float tabW = 195.0f;
    std::array<juce::TextButton, kPages> tabs;
    juce::ComboBox presetBox, skinBox;
    juce::TooltipWindow tooltips { this, 700 };
    std::unique_ptr<juce::FileChooser> chooser;

    int page = 0;
    float stripShift = 0.0f, animFrom = 0.0f, animTo = 0.0f;
    double animStart = 0.0;
    bool animating = false;
    int tick = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NShaperEditor)
};
