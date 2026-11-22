#include "PluginEditor.h"
#include "Presets.h"

using namespace juce;

//==============================================================================
// SKIN
namespace ui
{
const std::vector<Palette>& skins()
{
    static const std::vector<Palette> list = [] {
        std::vector<Palette> v;
        // FUMO (default): grigio fumo con accenti beige
        v.push_back ({ "SMOKE",
                       Colour (0xff2b2c30), Colour (0xff36383d), Colour (0xffc8c6c1), Colour (0xfff4f1ea),
                       Colour (0xff1b1c1f), Colour (0xfff4f1ea), Colour (0xffd8c8a6), Colour (0xffd8c8a6),
                       Colour (0xff1b1c1f), Colour (0xff1b1c1f).withAlpha (0.6f), Colour (0xffe6d3b0), Colour (0xffe07a5f),
                       Colour (0xff63666d), Colour (0xffefece6), Colour (0xffd8c8a6), Colour (0xffefdcb8),
                       { Colour (0xffefe4cc), Colour (0xffa9a49a), Colour (0xffd8b98a) } });
        // ABISSO: blu caldi e morbidi, nello spirito di soothe3
        v.push_back ({ "ABYSS",
                       Colour (0xff1d304b), Colour (0xff253c5c), Colour (0xffb5c8e2), Colour (0xfff2f7ff),
                       Colour (0xff13223a), Colour (0xfff2f7ff), Colour (0xff8ed2ff), Colour (0xff8ed2ff),
                       Colour (0xff13223a), Colour (0xff13223a).withAlpha (0.6f), Colour (0xffffb68a), Colour (0xffff6b7d),
                       Colour (0xff5a7ca8), Colour (0xffe4eeff), Colour (0xff8ed2ff), Colour (0xffffd6a6),
                       { Colour (0xff8ed2ff), Colour (0xffa9ecc4), Colour (0xffffb68a) } });
        // LUNA: nero, bianco, beige (la stessa di ULTRAMEGASUPERMAXICHORUS)
        v.push_back ({ "MOON",
                       Colour (0xff0b0b0c), Colour (0xff18181a), Colour (0xffe9e6df), Colour (0xffffffff),
                       Colour (0xff161618), Colour (0xffffffff), Colour (0xffd8c8a6), Colour (0xffe9e6df),
                       Colour (0xff0b0b0c), Colour (0xffffffff).withAlpha (0.07f), Colour (0xffd8c8a6), Colour (0xffe07a5f),
                       Colour (0xff55534f), Colour (0xffffffff), Colour (0xffd8c8a6), Colour (0xffefe4cc),
                       { Colour (0xffffffff), Colour (0xffb9b3a6), Colour (0xffd8c8a6) } });
        // CARTA: chiara
        v.push_back ({ "PAPER",
                       Colour (0xffece6da), Colour (0xffded6c6), Colour (0xff3a352e), Colour (0xff141210),
                       Colour (0xfff7f3ea), Colour (0xff141210), Colour (0xff141210), Colour (0xff141210),
                       Colour (0xffece6da), Colour (0xffffffff).withAlpha (0.55f), Colour (0xffc8553d), Colour (0xffd1342f),
                       Colour (0xffb9b0a0), Colour (0xff141210), Colour (0xff2f6f9f), Colour (0xffc8553d),
                       { Colour (0xff2f6f9f), Colour (0xff3d8a5a), Colour (0xffc8553d) } });
        // CARBONIO: nero e grigi, accenti bianchi e verdi
        v.push_back ({ "CARBON",
                       Colour (0xff111214), Colour (0xff1c1d20), Colour (0xffb9bcc0), Colour (0xffffffff),
                       Colour (0xff09090a), Colour (0xffffffff), Colour (0xff3ddc84), Colour (0xffffffff),
                       Colour (0xff0d0e0f), Colour (0xff000000).withAlpha (0.55f), Colour (0xff3ddc84), Colour (0xffff5a4f),
                       Colour (0xff4a4d52), Colour (0xfff2f2f2), Colour (0xff3ddc84), Colour (0xffffffff),
                       { Colour (0xffffffff), Colour (0xff9aa0a6), Colour (0xff3ddc84) } });
        // OSSIDO: marrone caldo e ruggine
        v.push_back ({ "OXIDE",
                       Colour (0xff2a211d), Colour (0xff342923), Colour (0xffd6c4b8), Colour (0xfffbf1ea),
                       Colour (0xff1a1411), Colour (0xfffbf1ea), Colour (0xffe0703a), Colour (0xffe0703a),
                       Colour (0xff1a1411), Colour (0xff1a1411).withAlpha (0.6f), Colour (0xfff0a05a), Colour (0xffff4d3d),
                       Colour (0xff6e5547), Colour (0xfff5e6da), Colour (0xffe0703a), Colour (0xfff5c08a),
                       { Colour (0xfff5c08a), Colour (0xffb8a597), Colour (0xffe0703a) } });
        // LILLA: grigio viola scuro, lilla e rosa
        v.push_back ({ "LILAC",
                       Colour (0xff24212c), Colour (0xff2d2937), Colour (0xffc9c1d8), Colour (0xfff6f2ff),
                       Colour (0xff17151d), Colour (0xfff6f2ff), Colour (0xffc3a6ff), Colour (0xffc3a6ff),
                       Colour (0xff17151d), Colour (0xff17151d).withAlpha (0.6f), Colour (0xffff9ecf), Colour (0xffff5c7a),
                       Colour (0xff5d5672), Colour (0xffefe9ff), Colour (0xffc3a6ff), Colour (0xffff9ecf),
                       { Colour (0xffc3a6ff), Colour (0xffa8e6cf), Colour (0xffff9ecf) } });
        // MENTA: chiara, verde
        v.push_back ({ "MINT",
                       Colour (0xffeef2ee), Colour (0xffe0e7e1), Colour (0xff33403a), Colour (0xff0f1a14),
                       Colour (0xfff9fbf9), Colour (0xff0f1a14), Colour (0xff1f8a5b), Colour (0xff0f1a14),
                       Colour (0xffeef2ee), Colour (0xffffffff).withAlpha (0.6f), Colour (0xff1f8a5b), Colour (0xffd1342f),
                       Colour (0xffb6c4bb), Colour (0xff0f1a14), Colour (0xff1f8a5b), Colour (0xff0f1a14),
                       { Colour (0xff2f6f9f), Colour (0xff1f8a5b), Colour (0xffc8553d) } });
        return v;
    }();
    return list;
}

Font font (float size, bool bold)
{
    return Font (FontOptions (size, bold ? Font::bold : Font::plain));
}
}

const ui::Palette& palOf (const Component& c)
{
    if (auto* fl = dynamic_cast<FlatLook*> (&c.getLookAndFeel()))
        return fl->pal();
    return ui::skins().front();
}

//==============================================================================
// GEOMETRIA: tutto costruito sullo stesso "squircle" (quadrato stondato)
namespace geo
{
constexpr float kN = 5.0f;

static Point<float> point (Point<float> c, float r, float a)
{
    const float s = std::sin (a), co = std::cos (a);
    const float k = std::pow (std::pow (std::abs (s), kN) + std::pow (std::abs (co), kN), -1.0f / kN);
    return { c.x + r * k * s, c.y - r * k * co };
}

static Path arc (Point<float> c, float r, float a0, float a1)
{
    Path p;
    const int steps = jmax (4, (int) std::ceil (std::abs (a1 - a0) / 0.025f));
    for (int i = 0; i <= steps; ++i)
    {
        const auto pt = point (c, r, a0 + (a1 - a0) * (float) i / (float) steps);
        if (i == 0) p.startNewSubPath (pt); else p.lineTo (pt);
    }
    return p;
}

static Path body (Point<float> c, float r)
{
    auto p = arc (c, r, 0.0f, MathConstants<float>::twoPi);
    p.closeSubPath();
    return p;
}
}

//==============================================================================
FlatLook::FlatLook() { setSkin (0); }

void FlatLook::setSkin (int index)
{
    skin = jlimit (0, (int) ui::skins().size() - 1, index);
    const auto& p = pal();
    setColour (PopupMenu::backgroundColourId,            p.band);
    setColour (PopupMenu::textColourId,                  p.text);
    setColour (PopupMenu::highlightedBackgroundColourId, p.fill);
    setColour (PopupMenu::highlightedTextColourId,       p.onFill);
    setColour (ComboBox::textColourId,                   p.strong);
    setColour (ComboBox::backgroundColourId,             p.field);
    setColour (ComboBox::outlineColourId,                Colours::transparentBlack);
    setColour (ComboBox::arrowColourId,                  p.text);
    setColour (TooltipWindow::backgroundColourId,        p.band);
    setColour (TooltipWindow::textColourId,              p.text);
    setColour (TooltipWindow::outlineColourId,           p.text.withAlpha (0.3f));
    setColour (Label::textColourId,                      p.text);
}

void FlatLook::drawRotarySlider (Graphics& g, int x, int y, int w, int h,
                                 float pos, float a0, float a1, Slider& s)
{
    const auto& p  = pal();
    const bool big = (bool) s.getProperties().getWithDefault ("big", false);
    const auto b   = Rectangle<int> (x, y, w, h).toFloat();
    const auto c   = b.getCentre();
    const float r     = jmin (b.getWidth(), b.getHeight()) * 0.5f - 2.0f;
    const float thick = big ? 4.0f : 2.5f;
    const float ang   = a0 + pos * (a1 - a0);
    const float ar    = r - thick * 0.5f;
    const PathStrokeType stroke (thick, PathStrokeType::mitered, PathStrokeType::butt);

    g.setColour (p.text.withAlpha (0.22f));
    g.strokePath (geo::arc (c, ar, a0, a1), stroke);

    const bool bipolar = s.getMinimum() < 0.0 && s.getMaximum() > 0.0;
    const float from   = bipolar ? a0 + (float) s.valueToProportionOfLength (0.0) * (a1 - a0) : a0;
    if (std::abs (ang - from) > 0.01f)
    {
        g.setColour (p.arc);
        g.strokePath (geo::arc (c, ar, jmin (from, ang), jmax (from, ang)), stroke);
    }

    const float br = r - thick - (big ? 7.0f : 4.0f);
    g.setColour (p.body);
    g.fillPath (geo::body (c, br));

    const auto p0 = geo::point (c, br * (big ? 0.45f : 0.3f), ang);
    const auto p1 = geo::point (c, br * 0.82f, ang);
    g.setColour (p.mark);
    g.drawLine (Line<float> (p0, p1), big ? 3.0f : 2.0f);
}

Label* FlatLook::createSliderTextBox (Slider& s)
{
    auto* l = LookAndFeel_V4::createSliderTextBox (s);
    l->setFont (ui::font (11.0f));
    l->setColour (Label::backgroundColourId, Colours::transparentBlack);
    l->setColour (Label::outlineColourId, Colours::transparentBlack);
    return l;
}

void FlatLook::drawButtonBackground (Graphics& g, Button& button, const Colour&, bool highlighted, bool)
{
    const auto& p = pal();
    auto b = button.getLocalBounds().toFloat();
    const auto kind = button.getProperties().getWithDefault ("kind", "").toString();
    const bool on = button.getToggleState();

    if (kind == "tab")
        return; // la barretta la disegna il contenuto, cosi' scorre

    b = b.reduced (0.5f);
    // switch in un unico riquadro: gli angoli interni (dove i pulsanti si toccano) restano vivi
    const auto side = button.getProperties().getWithDefault ("joined", "").toString();
    const bool roundL = side != "right" && side != "mid";
    const bool roundR = side != "left" && side != "mid";
    Path shape;
    shape.addRoundedRectangle (b.getX(), b.getY(), b.getWidth(), b.getHeight(), 4.0f, 4.0f,
                               roundL, roundR, roundL, roundR);
    if (on)
    {
        g.setColour (kind == "solo" ? p.accent : p.fill);
        g.fillPath (shape);
    }
    else
    {
        if (highlighted)
        {
            g.setColour (p.text.withAlpha (0.08f));
            g.fillPath (shape);
        }
        g.setColour (p.text.withAlpha (0.35f));
        g.strokePath (shape, PathStrokeType (1.0f));
    }
}

void FlatLook::drawButtonText (Graphics& g, TextButton& button, bool highlighted, bool)
{
    const auto& p = pal();
    const auto kind = button.getProperties().getWithDefault ("kind", "").toString();
    const bool on = button.getToggleState();
    g.setFont (ui::font (kind == "tab" ? 11.5f : 10.5f, true));

    if (kind == "tab")
        g.setColour (on ? p.strong : p.text.withAlpha (highlighted ? 0.85f : 0.55f));
    else
        g.setColour (on ? p.onFill : p.text);

    g.drawText (button.getButtonText(), button.getLocalBounds(), Justification::centred);
}

void FlatLook::drawComboBox (Graphics& g, int width, int height, bool, int, int, int, int, ComboBox&)
{
    const auto& p = pal();
    auto b = Rectangle<int> (0, 0, width, height).toFloat();
    g.setColour (p.field);
    g.fillRoundedRectangle (b, 4.0f);

    Path arrowPath;
    const float ax = (float) width - 14.0f, ay = (float) height * 0.5f;
    arrowPath.startNewSubPath (ax - 4.0f, ay - 2.0f);
    arrowPath.lineTo (ax, ay + 2.0f);
    arrowPath.lineTo (ax + 4.0f, ay - 2.0f);
    g.setColour (p.text);
    g.strokePath (arrowPath, PathStrokeType (1.4f));
}

void FlatLook::drawLinearSlider (Graphics& g, int x, int y, int w, int h, float pos, float minPos, float maxPos,
                                 Slider::SliderStyle style, Slider& s)
{
    if (style != Slider::TwoValueHorizontal)
    {
        LookAndFeel_V4::drawLinearSlider (g, x, y, w, h, pos, minPos, maxPos, style, s);
        return;
    }
    const auto& p = pal();
    const float cy = (float) y + (float) h * 0.5f;
    g.setColour (p.text.withAlpha (0.22f));
    g.fillRoundedRectangle ((float) x, cy - 1.5f, (float) w, 3.0f, 1.5f);
    g.setColour (p.arc);
    g.fillRoundedRectangle (minPos, cy - 1.5f, jmax (0.0f, maxPos - minPos), 3.0f, 1.5f);
    for (float px : { minPos, maxPos })
    {
        g.setColour (p.body);
        g.fillPath (geo::body ({ px, cy }, 7.0f));
        g.setColour (p.arc);
        g.strokePath (geo::body ({ px, cy }, 7.0f), PathStrokeType (2.0f));
    }
}

Font FlatLook::getComboBoxFont (ComboBox&) { return ui::font (12.0f); }
Font FlatLook::getPopupMenuFont()          { return ui::font (13.0f); }

void FlatLook::positionComboBoxText (ComboBox& box, Label& label)
{
    label.setBounds (8, 1, box.getWidth() - 26, box.getHeight() - 2);
    label.setFont (getComboBoxFont (box));
}

//==============================================================================
// MARCHIO
namespace brand
{
// un quadrato-squircle con dentro un rumore: il segnale che diventa una forma
static void drawMark (Graphics& g, Rectangle<float> box, const ui::Palette& p)
{
    const float u = box.getWidth() / 26.0f;
    const auto c = box.getCentre();
    g.setColour (p.accent);
    g.fillPath (geo::body (c, 12.0f * u));
    // rumore che si appiattisce verso destra
    static const float ys[] = { 0.0f, -5.5f, 4.5f, -3.0f, 6.0f, -6.0f, 2.5f, -2.0f, 1.5f, -1.0f, 0.6f, 0.0f };
    Path n;
    for (int i = 0; i < 12; ++i)
    {
        const Point<float> q (c.x - 8.0f * u + (float) i * 16.0f * u / 11.0f, c.y + ys[i] * u);
        if (i == 0) n.startNewSubPath (q); else n.lineTo (q);
    }
    g.setColour (p.onFill);
    g.strokePath (n, PathStrokeType (1.6f * u, PathStrokeType::mitered, PathStrokeType::rounded));
}

// N-SHAPER stirato fino a riempire il riquadro, con contorno dello stesso colore (piu' bold)
static void drawWordmark (Graphics& g, Rectangle<float> box, const ui::Palette& p)
{
    GlyphArrangement ga;
    ga.addLineOfText (ui::font (100.0f, true), "N-SHAPER", 0.0f, 0.0f);
    Path path;
    ga.createPath (path);
    const auto b = path.getBounds();
    if (b.isEmpty()) return;
    const float st = 1.1f;
    path.applyTransform (AffineTransform::translation (-b.getX(), -b.getY())
                             .scaled ((box.getWidth() - st) / b.getWidth(), (box.getHeight() - st) / b.getHeight())
                             .translated (box.getX() + st * 0.5f, box.getY() + st * 0.5f));
    g.setColour (p.strong);
    g.fillPath (path);
    g.strokePath (path, PathStrokeType (st, PathStrokeType::curved, PathStrokeType::rounded));
}
}

//==============================================================================
// utilita' comuni
namespace
{
constexpr float kLoHz = 20.0f, kHiHz = 20000.0f;

String hzText (float f)
{
    return f < 1000.0f ? String (roundToInt (f)) + " Hz" : String (f / 1000.0f, f < 10000.0f ? 2 : 1) + " kHz";
}
}

//==============================================================================
DetectTimeline::DetectTimeline (NShaperProcessor& p) : proc (p)
{
    setInterceptsMouseClicks (false, false);
    // parte dalla storia gia' registrata: aprendo la pagina si vede subito cosa e' successo
    const uint32_t w = proc.vis().histW.load();
    readPos = w > (uint32_t) smk::Vis::kHist ? w - (uint32_t) smk::Vis::kHist : 0u;
    startTimerHz (30);
}

void DetectTimeline::timerCallback()
{
    auto& v = proc.vis();
    const uint32_t w = v.histW.load();
    if (w - readPos > (uint32_t) smk::Vis::kHist) readPos = w - (uint32_t) smk::Vis::kHist;
    while (readPos != w)
    {
        const auto& h = v.hist[(size_t) (readPos % smk::Vis::kHist)];
        cols[(size_t) head] = { h.s.load(), h.f.load(), h.c.load(), h.d.load(), h.lvl.load() };
        head = (head + 1) % kCols;
        ++readPos;
    }
    repaint();
}

void DetectTimeline::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    auto b = getLocalBounds().toFloat();
    g.setColour (p.body);
    g.fillRoundedRectangle (b, 5.0f);
    auto r = b.reduced (6.0f, 6.0f);
    r.removeFromTop (14.0f);

    g.setFont (ui::font (9.5f, true));
    const char* names[] = { "S Z SH", "F V", "CH J" };
    float lx = b.getX() + 8.0f;
    for (int k = 0; k < 3; ++k)
    {
        g.setColour (p.cls[(size_t) k]);
        g.fillPath (geo::body ({ lx + 4.0f, b.getY() + 11.0f }, 3.5f));
        g.setColour (p.text.withAlpha (0.75f));
        g.drawText (names[k], Rectangle<float> (lx + 11.0f, b.getY() + 4.0f, 50.0f, 14.0f), Justification::centredLeft);
        lx += 58.0f;
    }
    g.setColour (p.text.withAlpha (0.45f));
    g.drawText ("last 3 s", Rectangle<float> (b.getRight() - 70.0f, b.getY() + 4.0f, 62.0f, 14.0f), Justification::centredRight);

    const float dx = r.getWidth() / (float) (kCols - 1);
    const float mid = r.getCentreY();

    // livello del segnale (forma d'onda tenue)
    {
        Path wv;
        wv.startNewSubPath (r.getX(), mid);
        for (int i = 0; i < kCols; ++i)
        {
            const auto& c = cols[(size_t) ((head + i) % kCols)];
            wv.lineTo (r.getX() + dx * (float) i, mid - c.lvl * c.lvl * r.getHeight() * 0.48f);
        }
        for (int i = kCols - 1; i >= 0; --i)
        {
            const auto& c = cols[(size_t) ((head + i) % kCols)];
            wv.lineTo (r.getX() + dx * (float) i, mid + c.lvl * c.lvl * r.getHeight() * 0.48f);
        }
        wv.closeSubPath();
        g.setColour (p.text.withAlpha (0.10f));
        g.fillPath (wv);
    }

    // rilevamento combinato (area) + classi (linee)
    {
        Path area;
        area.startNewSubPath (r.getX(), r.getBottom());
        for (int i = 0; i < kCols; ++i)
            area.lineTo (r.getX() + dx * (float) i, r.getBottom() - cols[(size_t) ((head + i) % kCols)].d * r.getHeight());
        area.lineTo (r.getRight(), r.getBottom());
        area.closeSubPath();
        g.setColour (p.strong.withAlpha (0.10f));
        g.fillPath (area);
    }
    for (int k = 0; k < 3; ++k)
    {
        // solo dove la classe e' presente: niente linee piatte sul fondo
        Path ln;
        bool open = false;
        for (int i = 0; i < kCols; ++i)
        {
            const auto& c = cols[(size_t) ((head + i) % kCols)];
            const float v = k == 0 ? c.s : (k == 1 ? c.f : c.c);
            const Point<float> pt (r.getX() + dx * (float) i, r.getBottom() - v * r.getHeight());
            if (v > 0.01f)
            {
                if (! open) { ln.startNewSubPath (pt.withY (r.getBottom())); open = true; }
                ln.lineTo (pt);
            }
            else if (open)
            {
                ln.lineTo (pt.withY (r.getBottom()));
                open = false;
            }
        }
        g.setColour (p.cls[(size_t) k]);
        g.strokePath (ln, PathStrokeType (1.4f));
    }
}

//==============================================================================
NsView::NsView (NShaperProcessor& p) : proc (p)
{
    sS.fill (-120.0f); sT.fill (-120.0f);
    startTimerHz (60);
}

float NsView::xOf (float hz) const
{
    const auto r = getLocalBounds().toFloat().reduced (1.0f);
    return r.getX() + r.getWidth() * std::log (jlimit (20.0f, 20000.0f, hz) / 20.0f) / std::log (1000.0f);
}

float NsView::hzOf (float x) const
{
    const auto r = getLocalBounds().toFloat().reduced (1.0f);
    return 20.0f * std::pow (1000.0f, jlimit (0.0f, 1.0f, (x - r.getX()) / r.getWidth()));
}

int NsView::hitEdge (float x) const
{
    const float a = xOf (proc.apvts.getRawParameterValue ("nsStart")->load());
    const float b = xOf (proc.apvts.getRawParameterValue ("nsEnd")->load());
    const float da = std::abs (x - a), dbb = std::abs (x - b);
    if (jmin (da, dbb) > 9.0f) return -1;
    return da <= dbb ? 0 : 1;
}

void NsView::timerCallback()
{
   #ifndef NSHAPER_SNAPSHOT
    if (! isShowing()) return;
   #endif
    auto& v = proc.vis();
    for (int i = 0; i < P; ++i)
    {
        sS[(size_t) i] += (v.nsS[(size_t) i].load() - sS[(size_t) i]) * 0.5f;
        sT[(size_t) i] += (v.nsT[(size_t) i].load() - sT[(size_t) i]) * 0.5f;
        sG[(size_t) i] += (v.nsG[(size_t) i].load() - sG[(size_t) i]) * 0.5f;
    }
    repaint();
}

void NsView::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    const auto r = getLocalBounds().toFloat().reduced (1.0f);
    g.setColour (p.body);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 5.0f);
    Graphics::ScopedSaveState ss (g);
    {
        Path cp;
        cp.addRoundedRectangle (getLocalBounds().toFloat(), 5.0f);
        g.reduceClipRegion (cp);
    }

    auto val = [this] (const char* id) { return proc.apvts.getRawParameterValue (id)->load(); };
    const bool on = true;
    const float fs = val ("nsStart"), fe = val ("nsEnd"), slope = val ("nsSlope");
    const int noise = (int) val ("nsNoise");

    // banda: piu' chiara dove N-SHAPER lavora, sfuma con la SLOPE
    for (int x = 0; x < (int) r.getWidth(); x += 2)
    {
        const float px = r.getX() + (float) x;
        const float w = smk::nsBandWeight (hzOf (px), fs, fe, slope);
        if (w > 0.01f)
        {
            g.setColour (p.accent.withAlpha (0.10f * w));
            g.fillRect (px, r.getY(), 2.0f, r.getHeight());
        }
    }
    g.setFont (ui::font (9.0f));
    for (int f : { 100, 1000, 10000 })
    {
        const float x = xOf ((float) f);
        g.setColour (p.text.withAlpha (0.07f));
        g.drawVerticalLine (roundToInt (x), r.getY(), r.getBottom());
        g.setColour (p.text.withAlpha (0.4f));
        g.drawText (f == 100 ? "100" : (f == 1000 ? "1k" : "10k"), Rectangle<float> (x + 3.0f, r.getBottom() - 13.0f, 30.0f, 12.0f), Justification::centredLeft);
    }

    auto xAt  = [this] (int i) { return xOf (20.0f * std::pow (1000.0f, ((float) i + 0.5f) / (float) P)); };
    auto ySp  = [&r] (float db) { return r.getY() + 8.0f + (r.getHeight() - 8.0f) * jlimit (0.0f, 1.0f, -db / 100.0f); };
    const float y0 = r.getY() + r.getHeight() * 0.5f;
    auto yG   = [&r, y0] (float db) { return y0 - jlimit (-24.0f, 24.0f, db) / 24.0f * r.getHeight() * 0.42f; };

    if (on)
    {
        // spettro misurato
        Path ps;
        ps.startNewSubPath (r.getX(), r.getBottom());
        for (int i = 0; i < P; ++i) ps.lineTo (xAt (i), ySp (sS[(size_t) i]));
        ps.lineTo (r.getRight(), r.getBottom());
        ps.closeSubPath();
        g.setColour (p.specIn.withAlpha (0.5f));
        g.fillPath (ps);

        // rumore bersaglio, solo dentro la banda
        Path pt;
        bool open = false;
        for (int i = 0; i < P; ++i)
        {
            const float x = xAt (i);
            if (smk::nsBandWeight (hzOf (x), fs, fe, slope) > 0.3f)
            {
                const Point<float> q (x, ySp (sT[(size_t) i]));
                if (! open) { pt.startNewSubPath (q); open = true; } else pt.lineTo (q);
            }
            else open = false;
        }
        g.setColour (p.curve);
        const float dashes[] = { 4.0f, 3.0f };
        Path dashed;
        PathStrokeType (1.6f).createDashedStroke (dashed, pt, dashes, 2);
        g.fillPath (dashed);

        // correzione applicata (+ alza, - taglia)
        g.setColour (p.text.withAlpha (0.18f));
        g.drawHorizontalLine (roundToInt (y0), r.getX(), r.getRight());
        Path pg, fill;
        fill.startNewSubPath (r.getX(), y0);
        for (int i = 0; i < P; ++i)
        {
            const Point<float> q (xAt (i), yG (sG[(size_t) i]));
            if (i == 0) pg.startNewSubPath (q); else pg.lineTo (q);
            fill.lineTo (q);
        }
        fill.lineTo (r.getRight(), y0);
        fill.closeSubPath();
        g.setColour (p.gr.withAlpha (0.25f));
        g.fillPath (fill);
        g.setColour (p.gr);
        g.strokePath (pg, PathStrokeType (1.6f));
    }

    // bordi trascinabili
    for (int e = 0; e < 2; ++e)
    {
        const float x = xOf (e == 0 ? fs : fe);
        const bool hot = e == drag || e == hover;
        g.setColour (p.accent.withAlpha (hot ? 1.0f : 0.7f));
        g.fillRect (x - 0.5f, r.getY(), 1.0f, r.getHeight());
        g.fillPath (geo::body ({ x, r.getY() + 10.0f }, hot ? 6.0f : 5.0f));
    }

    g.setFont (ui::font (10.0f, true));
    g.setColour (p.curve);
    String target;
    if (noise >= smk::kCustomNoise)
    {
        const auto* cn = proc.customNoise();
        target = cn != nullptr ? "CUSTOM  " + String (cn->name) : String ("CUSTOM: NO FILE (WHITE)");
    }
    else target = String (smk::noiseName (noise)) + " NOISE";
    g.drawText (target, Rectangle<float> (r.getX() + 8.0f, r.getY() + 4.0f, r.getWidth() - 16.0f, 14.0f), Justification::centredLeft);
    g.setColour (p.gr);
    g.drawText ("CORRECTION", Rectangle<float> (r.getX() + 8.0f, r.getY() + 18.0f, 140.0f, 14.0f), Justification::centredLeft);
}

void NsView::mouseMove (const MouseEvent& e)
{
    const int h = hitEdge (e.position.x);
    if (h != hover) { hover = h; repaint(); }
    setMouseCursor (h >= 0 ? MouseCursor::LeftRightResizeCursor : MouseCursor::NormalCursor);
}

void NsView::mouseDown (const MouseEvent& e)
{
    drag = hitEdge (e.position.x);
    if (drag >= 0)
        if (auto* prm = proc.apvts.getParameter (drag == 0 ? "nsStart" : "nsEnd")) prm->beginChangeGesture();
}

void NsView::mouseDrag (const MouseEvent& e)
{
    if (drag < 0) return;
    if (auto* prm = proc.apvts.getParameter (drag == 0 ? "nsStart" : "nsEnd"))
    {
        float f = hzOf (e.position.x);
        const float other = proc.apvts.getRawParameterValue (drag == 0 ? "nsEnd" : "nsStart")->load();
        f = drag == 0 ? jmin (f, other / 1.06f) : jmax (f, other * 1.06f);
        prm->setValueNotifyingHost (prm->convertTo0to1 (f));
    }
}

void NsView::mouseUp (const MouseEvent&)
{
    if (drag >= 0)
        if (auto* prm = proc.apvts.getParameter (drag == 0 ? "nsStart" : "nsEnd")) prm->endChangeGesture();
    drag = -1;
}

//==============================================================================
NsMeter::NsMeter (NShaperProcessor& p) : proc (p)
{
    setInterceptsMouseClicks (false, false);
    startTimerHz (30);
}

void NsMeter::timerCallback()
{
    auto& v = proc.vis();
    const float l = v.nsLevel.load();
    level = l > level ? l : level + (l - level) * 0.25f;
    ref = v.nsRef.load();
    amt += (v.nsAmtNow.load() - amt) * 0.4f;
    repaint();
}

void NsMeter::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    auto b = getLocalBounds().toFloat();
    g.setColour (p.body);
    g.fillRoundedRectangle (b, 5.0f);
    auto r = b.reduced (10.0f, 8.0f);

    const bool on = true;
    auto xOf = [&r] (float db) { return r.getX() + r.getWidth() * jlimit (0.0f, 1.0f, (db + 90.0f) / 90.0f); };

    g.setFont (ui::font (9.5f, true));
    g.setColour (p.text.withAlpha (0.7f));
    g.drawText ("BAND LEVEL", r.removeFromTop (13.0f), Justification::centredLeft);

    auto bar = r.removeFromTop (10.0f);
    g.setColour (p.text.withAlpha (0.15f));
    g.fillRoundedRectangle (bar, 2.0f);
    // i 60 dB su cui DYNAMIC misura la presenza: dal picco recente in giu'
    if (on)
    {
        g.setColour (p.accent.withAlpha (0.2f));
        g.fillRect (Rectangle<float>::leftTopRightBottom (xOf (ref - 60.0f), bar.getY(), xOf (ref), bar.getBottom()));
        g.setColour (p.arc);
        g.fillRoundedRectangle (bar.withRight (xOf (level)), 2.0f);
        g.setColour (p.accent);
        g.fillRect (xOf (ref) - 1.0f, bar.getY() - 3.0f, 2.0f, bar.getHeight() + 6.0f);
    }

    r.removeFromTop (6.0f);
    g.setFont (ui::font (9.5f));
    g.setColour (p.text.withAlpha (0.55f));
    g.drawText ("-90", r.withHeight (12.0f), Justification::centredLeft);
    g.drawText ("0 dB", r.withHeight (12.0f), Justification::centredRight);
    r.removeFromTop (16.0f);
    g.setFont (ui::font (10.5f, true));
    g.setColour (p.strong);
    g.drawText (on ? "AMOUNT NOW  " + String (roundToInt (amt * 100.0f)) + " %" : String ("N-SHAPER OFF"), r.withHeight (14.0f), Justification::centredLeft);
}

//==============================================================================
Meters::Meters (NShaperProcessor& p) : proc (p)
{
    setInterceptsMouseClicks (false, false);
    startTimerHz (30);
}

void Meters::timerCallback()
{
    auto& v = proc.vis();
    const float i = Decibels::gainToDecibels (v.inPeak.load(), -90.0f);
    const float o = Decibels::gainToDecibels (v.outPeak.load(), -90.0f);
    in  = i > in  ? i : in  - 1.5f;
    out = o > out ? o : out - 1.5f;
    if (i >= inPk)  { inPk = i;  inHold = 30; } else if (--inHold < 0)  inPk -= 1.0f;
    if (o >= outPk) { outPk = o; outHold = 30; } else if (--outHold < 0) outPk -= 1.0f;
    gr += (v.grNow.load() - gr) * 0.35f;
    repaint();
}

void Meters::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    auto b = getLocalBounds().toFloat();
    const float colW = b.getWidth() / 3.0f;
    const char* names[] = { "IN", "GR", "OUT" };

    for (int k = 0; k < 3; ++k)
    {
        auto c = b.withX (b.getX() + colW * (float) k).withWidth (colW);
        auto lab = c.removeFromBottom (13.0f);
        auto val = c.removeFromBottom (13.0f);
        auto bar = c.withSizeKeepingCentre (10.0f, c.getHeight() - 4.0f);

        g.setColour (p.body);
        g.fillRoundedRectangle (bar, 2.0f);

        float frac = 0.0f, pk = -1.0f;
        String txt;
        if (k == 1)
        {
            frac = jlimit (0.0f, 1.0f, gr / 24.0f);
            g.setColour (p.gr);
            g.fillRoundedRectangle (bar.withHeight (bar.getHeight() * frac), 2.0f);
            txt = String (gr, 1);
        }
        else
        {
            const float lv = k == 0 ? in : out, pkv = k == 0 ? inPk : outPk;
            frac = jlimit (0.0f, 1.0f, (lv + 60.0f) / 60.0f);
            pk = jlimit (0.0f, 1.0f, (pkv + 60.0f) / 60.0f);
            g.setColour (lv > -0.3f ? p.hot : p.arc);
            g.fillRoundedRectangle (bar.withTop (bar.getBottom() - bar.getHeight() * frac), 2.0f);
            if (pk > 0.0f)
            {
                g.setColour (p.strong.withAlpha (0.8f));
                g.fillRect (bar.getX(), bar.getBottom() - bar.getHeight() * pk, bar.getWidth(), 1.5f);
            }
            txt = pkv <= -89.0f ? String ("-inf") : String (pkv, 1);
        }
        g.setFont (ui::font (9.5f));
        g.setColour (p.strong);
        g.drawText (txt, val, Justification::centred);
        g.setFont (ui::font (9.5f, true));
        g.setColour (p.text.withAlpha (0.7f));
        g.drawText (names[k], lab, Justification::centred);
    }
}

//==============================================================================
DetectLights::DetectLights (NShaperProcessor& p) : proc (p)
{
    setInterceptsMouseClicks (false, false);
    startTimerHz (30);
}

void DetectLights::timerCallback()
{
    auto& v = proc.vis();
    const float now[] = { v.sib.load(), v.fv.load(), v.cg.load() };
    for (size_t k = 0; k < 3; ++k)
        lv[k] = now[k] > lv[k] ? now[k] : lv[k] * 0.82f;
    repaint();
}

void DetectLights::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    auto b = getLocalBounds().toFloat();
    const char* names[] = { "S Z SH", "F V", "CH J" };
    const char* ids[]   = { "detS", "detF", "detC" };
    float x = b.getX();
    g.setFont (ui::font (9.5f, true));
    for (int k = 0; k < 3; ++k)
    {
        const bool en = proc.apvts.getRawParameterValue (ids[k])->load() > 0.5f;
        const Point<float> c (x + 5.0f, b.getCentreY());
        g.setColour (p.text.withAlpha (0.2f));
        g.fillPath (geo::body (c, 4.0f));
        if (en && lv[(size_t) k] > 0.02f)
        {
            g.setColour (p.cls[(size_t) k].withAlpha (jlimit (0.0f, 1.0f, lv[(size_t) k])));
            g.fillPath (geo::body (c, 4.0f));
        }
        g.setColour (p.text.withAlpha (en ? 0.75f : 0.3f));
        g.drawText (names[k], Rectangle<float> (x + 13.0f, b.getY(), 52.0f, b.getHeight()), Justification::centredLeft);
        x += 66.0f;
    }
    g.setColour (p.text.withAlpha (0.5f));
    g.setFont (ui::font (9.5f));
    g.drawText ("LATENCY " + String (proc.latencyMs()) + " ms", b, Justification::centredRight);
}

//==============================================================================
// EDITOR
void NShaperEditor::Content::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    g.fillAll (p.bg);
    g.setColour (p.band);
    g.fillRect (0, 0, baseW, pageY);
    g.fillRect (0, pageY + pageH, baseW, baseH - pageY - pageH);

    brand::drawMark (g, { 16.0f, 14.0f, 26.0f, 26.0f }, p);
    brand::drawWordmark (g, { 50.0f, 18.0f, 114.0f, 18.0f }, p);

    g.setColour (p.strong);
    g.fillRect (tabX + 10.0f, (float) pageY - 2.0f, NShaperEditor::tabW - 20.0f, 2.0f);
}

void NShaperEditor::Page::paint (Graphics& g)
{
    const auto& p = palOf (*this);
    g.setColour (p.text.withAlpha (0.75f));
    g.setFont (ui::font (11.0f));
    if (index == 0)
    {
        g.setFont (ui::font (10.0f, true));
        g.drawText ("RESOLUTION", Rectangle<int> (306, 380, 100, 14), Justification::centred);
        g.setFont (ui::font (9.5f));
        g.setColour (p.text.withAlpha (0.5f));
        g.drawFittedText ("LIVE = zero latency", Rectangle<int> (306, 396, 100, 24), Justification::centredTop, 2);
    }
    if (index == 1)
        g.drawFittedText ("What to detect, and how easily. Used in SIBILANTS mode. The lights react in real time; "
                          "below you see the last 3 seconds.",
                          Rectangle<int> (16, 8, 390, 30), Justification::topLeft, 2);
}

NShaperEditor::NShaperEditor (NShaperProcessor& p)
    : AudioProcessorEditor (&p), proc (p),
      timeline (p), meters (p), lights (p), nsView (p), nsMeter (p)
{
    setLookAndFeel (&look);
    look.setSkin (proc.uiSkin.load());

    addAndMakeVisible (content);
    content.addAndMakeVisible (clip);
    clip.addAndMakeVisible (strip);
    for (auto* pg : { &pNoise, &pDetect }) strip.addAndMakeVisible (*pg);
    content.addAndMakeVisible (meters);
    content.addAndMakeVisible (lights);

    // --- N-SHAPER
    pNoise.addAndMakeVisible (nsView);
    for (auto* b : { &nsSibBtn, &nsFullBtn })
    {
        b->getProperties().set ("kind", "seg");
        pNoise.addAndMakeVisible (*b);
    }
    nsSibBtn.getProperties().set ("joined", "left");
    nsFullBtn.getProperties().set ("joined", "right");
    nsSibBtn.setTooltip ("Works only on the consonants the detector finds: S Z SH, F V, CH J (DETECT page).");
    nsFullBtn.setTooltip ("Works on the whole signal, all the time.");
    nsSibBtn.onClick  = [this] { setParam ("nsFull", 0.0f); };
    nsFullBtn.onClick = [this] { setParam ("nsFull", 1.0f); };
    for (int i = 0; i < smk::kNumNoises; ++i)
        nsNoiseBox.addItem (smk::noiseName (i), i + 1);
    nsNoiseBox.addItem ("CUSTOM", smk::kCustomNoise + 1);
    nsNoiseAtt = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (proc.apvts, "nsNoise", nsNoiseBox);
    nsNoiseBox.setTooltip ("Noise to match.\nWHITE flat, PINK -3 dB/oct, BROWN -6 dB/oct, BLUE +3, VIOLET +6.\n"
                           "GREY: flat to the ear (inverse A-weighting). BREATH: pink with an aspiration bump around 2.5 kHz.\n"
                           "SILK: almost flat with soft air. SMOKE: dark, with flat hiss above 4 kHz. TAPE: hiss bump at 6 kHz, rolled-off top.\n"
                           "CUSTOM: the average spectrum of the file you load with LOAD.");
    pNoise.addAndMakeVisible (nsNoiseBox);
    noiseLoadBtn.setButtonText ("LOAD");
    noiseLoadBtn.setTooltip ("Load your own noise (or any sound) from the Finder: its average spectrum becomes the target shape. "
                             "WAV, AIFF, FLAC, MP3, M4A, CAF. Silent parts are ignored. Selects CUSTOM.");
    noiseClearBtn.setTooltip ("Forget the custom noise (CUSTOM falls back to white).");
    noiseLoadBtn.onClick = [this] { chooseNoise(); };
    noiseClearBtn.onClick = [this] { proc.clearNoise(); nsView.repaint(); };
    pNoise.addAndMakeVisible (noiseLoadBtn);
    pNoise.addAndMakeVisible (noiseClearBtn);

    nsRange.setNormalisableRange ([] { NormalisableRange<double> r (20.0, 20000.0); r.setSkewForCentre (1000.0); return r; }());
    nsRange.setTooltip ("Band to reshape: drag the two ends (or the lines in the display).");
    nsRange.onDragStart = [this]
    {
        nsRangeDragging = true;
        for (auto* id : { "nsStart", "nsEnd" }) if (auto* prm = proc.apvts.getParameter (id)) prm->beginChangeGesture();
    };
    nsRange.onValueChange = [this]
    {
        if (! nsRangeDragging) return;
        for (auto* id : { "nsStart", "nsEnd" })
            if (auto* prm = proc.apvts.getParameter (id))
                prm->setValueNotifyingHost (prm->convertTo0to1 ((float) (String (id) == "nsStart" ? nsRange.getMinValue() : nsRange.getMaxValue())));
    };
    nsRange.onDragEnd = [this]
    {
        for (auto* id : { "nsStart", "nsEnd" }) if (auto* prm = proc.apvts.getParameter (id)) prm->endChangeGesture();
        nsRangeDragging = false;
    };
    pNoise.addAndMakeVisible (nsRange);
    for (auto* l : { &nsStartLbl, &nsEndLbl })
    {
        l->setFont (ui::font (10.0f, true));
        l->setInterceptsMouseClicks (false, false);
        pNoise.addAndMakeVisible (*l);
    }
    nsStartLbl.setJustificationType (Justification::centredLeft);
    nsEndLbl.setJustificationType (Justification::centredRight);
    setupKnob (nsSlope,  pNoise, "nsSlope",  "SLOPE",  "Steepness of both band edges. Low: the reshaping fades in over octaves. High: a sharp window.");
    setupKnob (nsAmount, pNoise, "nsAmount", "AMOUNT", "How far the band moves toward the noise shape. 100% = matched (boosts are limited to +18 dB).");
    setupKnob (nsMakeup, pNoise, "nsMakeup", "MAKEUP", "Gain inside the band only (following the SLOPE edges). In SIBILANTS mode only on detected consonants.");
    setupKnob (nsSpeed,  pNoise, "nsSpeed",  "SPEED",  "How fast the measured spectrum follows the signal. Short = reacts to each consonant, long = smoother.");
    setupKnob (nsDetail, pNoise, "nsDetail", "DETAIL", "Resolution of the matching: low = broad tilt (1 octave), high = fine detail (1/24 octave).");
    setupKnob (nsDynamic, pNoise, "nsDynamic", "DYNAMIC", "How much the intervention follows the signal in the band, gradually. 0%: same amount at any level. "
                                                          "100%: full on strong signal, less and less as it gets quieter, none in silence. Presence is measured against the band's own recent peaks over 60 dB.");
    pNoise.addAndMakeVisible (nsMeter);
    for (int i = 0; i < smk::Engine::kNumRes; ++i)
        resBox.addItem (i == 0 ? String ("LIVE  0 ms") : String (proc.bandsFor (i)) + " bands", i + 1);
    resAtt = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (proc.apvts, "res", resBox);
    {
        String tip = "Number of bands. More bands = more frequency precision, but longer windows: more latency and more CPU.\n\n"
                     "LIVE: zero latency, for singing through it on stage or while tracking. Same analysis at 513 bands, "
                     "applied with a minimum-phase filter updated every ~3 ms. No lookahead, so the first ~10-15 ms "
                     "of each consonant pass through untouched.\n";
        for (int i = 1; i < smk::Engine::kNumRes; ++i)
            tip << "\n" << proc.bandsFor (i) << " bands: latency " << proc.latencyMsFor (i) << " ms";
        resBox.setTooltip (tip);
    }
    pNoise.addAndMakeVisible (resBox);

    // --- DETECT
    setupToggle (detS, pDetect, "detS", "S  Z  SH", "Sibilants: S, Z (also Italian TS) and SH.");
    setupToggle (detF, pDetect, "detF", "F  V", "Labiodental fricatives: F and V.");
    setupToggle (detC, pDetect, "detC", "CH  J", "Affricates: CH and J sounds (Italian soft C and G): a burst followed by hiss. "
                                                 "T, K and P bursts are recognised and left alone.");
    setupKnob (sensS, pDetect, "sensS", "SENS", "Sensitivity for sibilants.");
    setupKnob (sensF, pDetect, "sensF", "SENS", "Sensitivity for F and V.");
    setupKnob (sensC, pDetect, "sensC", "SENS", "Sensitivity for CH and J (also makes softer bursts count).");
    setupKnob (hold,  pDetect, "hold",  "HOLD",  "How long detection stays on after the consonant.");
    setupKnob (guard, pDetect, "guard", "GUARD", "Vowel protection: where there is pitched voice, detection switches off.");
    pDetect.addAndMakeVisible (timeline);

    // --- piede
    setupKnob (mix,    content, "mix",    "MIX",    "Dry/wet of the whole plugin.");
    setupKnob (output, content, "output", "OUTPUT", "Output volume.");
    setupToggle (delta,  content, "delta",  "DELTA", "Listen only to what N-SHAPER changes.", "solo");
    setupToggle (listen, content, "listen", "CONS. ONLY", "Listen only to the detected consonants (already processed). Handy for tuning the detector.", "solo");

    const char* tabNames[] = { "N-SHAPER", "DETECT" };
    for (int i = 0; i < kPages; ++i)
    {
        auto& t = tabs[(size_t) i];
        t.setButtonText (tabNames[i]);
        t.getProperties().set ("kind", "tab");
        t.onClick = [this, i] { showPage (i, true); };
        content.addAndMakeVisible (t);
    }

    presetBox.setTextWhenNothingSelected ("Preset");
    for (int i = 0; i < (int) smkp::presets().size(); ++i)
        presetBox.addItem (smkp::presets()[(size_t) i].name, i + 1);
    presetBox.onChange = [this]
    {
        const int id = presetBox.getSelectedId();
        if (id > 0) proc.applyPreset (id - 1);
    };
    content.addAndMakeVisible (presetBox);

    for (int i = 0; i < (int) ui::skins().size(); ++i)
        skinBox.addItem (ui::skins()[(size_t) i].name, i + 1);
    skinBox.setSelectedId (look.getSkin() + 1, dontSendNotification);
    skinBox.setTooltip ("Changes the interface colours. The sound does not change.");
    skinBox.onChange = [this] { applySkin (skinBox.getSelectedId() - 1); };
    content.addAndMakeVisible (skinBox);

    setResizable (true, true);
    setResizeLimits ((int) (baseW * 0.8f), (int) (baseH * 0.8f), (int) (baseW * 2.0f), (int) (baseH * 2.0f));
    if (auto* con = getConstrainer())
        con->setFixedAspectRatio ((double) baseW / (double) baseH);
    setSize (baseW, baseH);

    applySkin (look.getSkin());
    showPage (proc.uiPage.load(), false);
    timerCallback();
    startTimerHz (60);
}

NShaperEditor::~NShaperEditor()
{
    stopTimer();
    setLookAndFeel (nullptr);
}

std::vector<NShaperEditor::Knob*> NShaperEditor::allKnobs()
{
    return { &sensS, &sensF, &sensC, &hold, &guard,
             &nsSlope, &nsAmount, &nsMakeup, &nsSpeed, &nsDetail, &nsDynamic, &mix, &output };
}

void NShaperEditor::applySkin (int index)
{
    look.setSkin (index);
    proc.uiSkin = look.getSkin();
    const auto& p = look.pal();
    for (auto* k : allKnobs())
    {
        k->slider.setColour (Slider::textBoxTextColourId, p.strong);
        k->name.setColour (Label::textColourId, p.text.withAlpha (0.75f));
    }
    nsStartLbl.setColour (Label::textColourId, p.text.withAlpha (0.8f));
    nsEndLbl.setColour (Label::textColourId, p.text.withAlpha (0.8f));
    sendLookAndFeelChange();
    repaint();
}

void NShaperEditor::setParam (const char* id, float value)
{
    if (auto* prm = proc.apvts.getParameter (id))
    {
        prm->beginChangeGesture();
        prm->setValueNotifyingHost (prm->convertTo0to1 (value));
        prm->endChangeGesture();
    }
}

void NShaperEditor::setupKnob (Knob& k, Component& parent, const String& paramId, const String& label, const String& tip, bool big)
{
    auto& s = k.slider;
    s.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s.setTextBoxStyle (Slider::TextBoxBelow, true, 80, 16);
    s.setColour (Slider::textBoxOutlineColourId,    Colours::transparentBlack);
    s.setColour (Slider::textBoxBackgroundColourId, Colours::transparentBlack);
    s.setTooltip (tip);
    if (big) s.getProperties().set ("big", true);

    k.att = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (proc.apvts, paramId, s);
    if (auto* prm = proc.apvts.getParameter (paramId))
        s.setDoubleClickReturnValue (true, prm->convertFrom0to1 (prm->getDefaultValue()));
    parent.addAndMakeVisible (s);

    k.name.setText (label, dontSendNotification);
    k.name.setJustificationType (Justification::centred);
    k.name.setFont (ui::font (10.0f, true));
    k.name.setInterceptsMouseClicks (false, false);
    parent.addAndMakeVisible (k.name);
}

void NShaperEditor::setupToggle (Toggle& t, Component& parent, const String& paramId, const String& text, const String& tip, const String& kind)
{
    t.button.setButtonText (text);
    t.button.setClickingTogglesState (true);
    t.button.setTooltip (tip);
    if (kind.isNotEmpty()) t.button.getProperties().set ("kind", kind);
    t.att = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment> (proc.apvts, paramId, t.button);
    parent.addAndMakeVisible (t.button);
}

void NShaperEditor::placeKnob (Knob& k, Rectangle<int> cell)
{
    k.name.setBounds (cell.removeFromTop (16));
    k.slider.setBounds (cell.reduced (4, 0));
}

void NShaperEditor::showPage (int newPage, bool animate)
{
    page = jlimit (0, kPages - 1, newPage);
    proc.uiPage = page;
    for (int i = 0; i < kPages; ++i)
        tabs[(size_t) i].setToggleState (i == page, dontSendNotification);

    animTo = (float) (page * baseW);
    if (animate)
    {
        animFrom = stripShift;
        animStart = Time::getMillisecondCounterHiRes();
        animating = std::abs (animTo - animFrom) > 0.5f;
    }
    if (! animate || ! animating)
    {
        stripShift = animTo;
        animating = false;
    }
    strip.setTopLeftPosition (-roundToInt (stripShift), 0);
    content.tabX = 16.0f + tabW * stripShift / (float) baseW;
    content.repaint();
}

void NShaperEditor::chooseNoise()
{
    chooser = std::make_unique<FileChooser> ("Choose a noise", File::getSpecialLocation (File::userHomeDirectory),
                                             "*.wav;*.aif;*.aiff;*.flac;*.mp3;*.m4a;*.caf;*.ogg");
    chooser->launchAsync (FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles,
                          [this] (const FileChooser& fc)
                          {
                              const auto f = fc.getResult();
                              if (f.existsAsFile() && ! proc.loadNoise (f))
                                  AlertWindow::showMessageBoxAsync (MessageBoxIconType::WarningIcon, "N-Shaper", "Unreadable audio file.");
                              nsView.repaint();
                          });
}

void NShaperEditor::paint (Graphics& g)
{
    g.fillAll (look.pal().band);
}

void NShaperEditor::resized()
{
    const float s = (float) getWidth() / (float) baseW;
    content.setBounds (0, 0, baseW, baseH);
    content.setTransform (AffineTransform::scale (s));

    // testata
    presetBox.setBounds (172, 14, 132, 26);
    skinBox.setBounds (312, 14, 94, 26);
    for (int i = 0; i < kPages; ++i)
        tabs[(size_t) i].setBounds (16 + roundToInt ((float) i * tabW), 52, roundToInt (tabW), 32);

    // pagine (coordinate locali: 422 x 434)
    clip.setBounds (0, pageY, baseW, pageH);
    strip.setBounds (-roundToInt (stripShift), 0, baseW * kPages, pageH);
    pNoise.setBounds (0, 0, baseW, pageH);
    pDetect.setBounds (baseW, 0, baseW, pageH);

    // N-SHAPER: switch, rumore, carica, X — 8 px tra i riquadri
    nsSibBtn.setBounds (16, 10, 92, 26);   // un unico switch: i due bordi si sovrappongono di 1 px
    nsFullBtn.setBounds (107, 10, 93, 26);
    nsNoiseBox.setBounds (208, 10, 98, 26);
    noiseLoadBtn.setBounds (314, 10, 56, 26);
    noiseClearBtn.setBounds (378, 10, 28, 26);
    nsView.setBounds (16, 44, 390, 158);
    nsRange.setBounds (8, 204, 406, 24);
    nsStartLbl.setBounds (16, 226, 160, 14);
    nsEndLbl.setBounds (246, 226, 160, 14);
    Knob* nk[] = { &nsSlope, &nsAmount, &nsMakeup, &nsSpeed, &nsDetail };
    for (int i = 0; i < 5; ++i)
        placeKnob (*nk[i], { 16 + i * 78, 246, 78, 84 });
    placeKnob (nsDynamic, { 16, 338, 78, 84 });
    nsMeter.setBounds (102, 346, 196, 72);
    resBox.setBounds (306, 346, 100, 26);

    // DETECT: tre colonne (interruttore + sensibilita'), poi HOLD/GUARD, poi la storia
    Toggle* dt[] = { &detS, &detF, &detC };
    Knob* sk[]   = { &sensS, &sensF, &sensC };
    for (int i = 0; i < 3; ++i)
    {
        const int x0 = 16 + i * 130;
        dt[i]->button.setBounds (x0 + 10, 44, 110, 26);
        placeKnob (*sk[i], { x0 + 26, 76, 78, 84 });
    }
    placeKnob (hold,  { 133, 168, 78, 84 });
    placeKnob (guard, { 211, 168, 78, 84 });
    timeline.setBounds (16, 262, 390, 162);

    // piede
    placeKnob (mix,    { 16, 526, 78, 84 });
    placeKnob (output, { 94, 526, 78, 84 });
    delta.button.setBounds (182, 534, 108, 28);
    listen.button.setBounds (182, 570, 108, 28);
    meters.setBounds (300, 528, 106, 82);
    lights.setBounds (16, 616, 390, 18);
}

void NShaperEditor::timerCallback()
{
    if (animating)
    {
        const double t = jlimit (0.0, 1.0, (Time::getMillisecondCounterHiRes() - animStart) / pageAnimMs);
        // ease-out esponenziale: scatto deciso, frenata lunga e morbida
        const float e = (1.0f - std::exp2 (-7.0f * (float) t)) / (1.0f - std::exp2 (-7.0f));
        stripShift = animFrom + (animTo - animFrom) * e;
        if (t >= 1.0) { stripShift = animTo; animating = false; }
        strip.setTopLeftPosition (-roundToInt (stripShift), 0);
        content.tabX = 16.0f + tabW * stripShift / (float) baseW;
        content.repaint (0, pageY - 3, baseW, 4);
    }

    if (++tick % 4 != 0) return;

    auto val = [this] (const char* id) { return proc.apvts.getRawParameterValue (id)->load(); };
    const bool full = val ("nsFull") > 0.5f;
    nsSibBtn.setToggleState (! full, dontSendNotification);
    nsFullBtn.setToggleState (full, dontSendNotification);
    if (! nsRangeDragging)
        nsRange.setMinAndMaxValues (val ("nsStart"), val ("nsEnd"), dontSendNotification);
    auto hzT = [] (float f) { return f < 1000.0f ? String (roundToInt (f)) + " Hz" : String (f / 1000.0f, f < 10000.0f ? 2 : 1) + " kHz"; };
    nsStartLbl.setText ("START  " + hzT (val ("nsStart")), dontSendNotification);
    nsEndLbl.setText ("END  " + hzT (val ("nsEnd")), dontSendNotification);
    noiseClearBtn.setEnabled (proc.customNoise() != nullptr);

    // DELTA e SOLO CONS. si escludono a vicenda
    if (delta.button.getToggleState() && listen.button.getToggleState())
        setParam ("listen", 0.0f);
}
