#!/bin/bash
# Installa N-Shaper (AU + VST3) nella tua cartella utente. Smoker non viene toccato.
cd "$(dirname "$0")" || exit 1

COMP_DIR="$HOME/Library/Audio/Plug-Ins/Components"
VST_DIR="$HOME/Library/Audio/Plug-Ins/VST3"
mkdir -p "$COMP_DIR" "$VST_DIR"

# toglie la versione precedente di N-Shaper
rm -rf "$COMP_DIR/N-Shaper.component" "$VST_DIR/N-Shaper.vst3"
cp -R N-Shaper.component "$COMP_DIR/"
cp -R N-Shaper.vst3 "$VST_DIR/"

xattr -dr com.apple.quarantine "$COMP_DIR/N-Shaper.component" 2>/dev/null
xattr -dr com.apple.quarantine "$VST_DIR/N-Shaper.vst3" 2>/dev/null
killall -9 AudioComponentRegistrar 2>/dev/null

echo ""
echo "Fatto. Riapri Logic: lo trovi in Audio Units > CONTROLUNA > N-Shaper."
