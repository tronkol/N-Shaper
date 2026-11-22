# N-Shaper (CONTROLUNA)

Plugin AU / VST3 per macOS. Nasce da SMOKER: l'algoritmo principale (spectral dynamics) e la texture sono stati tolti,
la pagina N-SHAPER e' diventata il plugin.

## Cosa fa
Nella banda START-END porta lo spettro verso la forma di un rumore, al livello medio della banda (taglia e alza).
- **SIBILANTS**: lavora solo sulle consonanti trovate dal detector (S Z SH, F V, CH J).
- **FULL SIGNAL**: lavora sempre, su tutto.
- Rumori: WHITE, PINK, BROWN, BLUE, VIOLET, GREY, BREATH, SILK, SMOKE, TAPE e **CUSTOM**.
- **LOAD**: carichi un file audio qualsiasi (WAV, AIFF, FLAC, MP3, M4A, CAF). Il suo spettro medio (le parti silenziose
  non contano) diventa la forma bersaglio. Il percorso viene salvato nel progetto. **X** lo toglie (CUSTOM torna bianco).
- SLOPE, AMOUNT, MAKEUP, SPEED, DETAIL, DYNAMIC come prima. Risoluzione da LIVE (0 ms) a 8193 bande.

## Detector (pagina DETECT), riscritto
- Oltre alla finestra da 43 ms ora c'e' un inviluppo fine (1 ms) delle alte:
  - **CH / J**: riconosciuti dall'esplosione seguita da frizione che dura, anche con la chiusura sonora della J.
  - **T / K / P**: l'esplosione e il soffio dopo non vengono piu' presi per S o F.
  - **TS** (z italiana) resta nel gruppo S.
  - la "sbavatura" della finestra lunga (un'esplosione o la coda di una S sul bordo) non conta piu'.
- **Fondo del rumore** in tre fasce: un fruscio fermo non accende mai il detector, una F debole sopra il fruscio si'.
- **V**: la barra di sonorita' non la fa piu' scambiare per una vocale.

Prove su parlato sintetico (7 condizioni: voce maschile/femminile, piano, rumore di fondo, stanza, MP3, parlato veloce):

| | SMOKER 1.8 | N-Shaper |
|---|---|---|
| S Z SH riconosciute | 88/91 | 90/91 |
| F V riconosciute | 70/77 | 77/77 |
| CH J riconosciute | 18/63 | 62/63 |
| T K P scambiate per consonanti | 38/42 | 8/42 |

## Skin
SMOKE (default), ABYSS, MOON, PAPER, **CARBON** (nero/grigio, accenti bianchi e verdi), OXIDE, LILAC, MINT.

## Build
GitHub Actions (`.github/workflows/build-macos.yml`, runner macos-15) produce `N-Shaper-macOS.zip` con
`N-Shaper.component`, `N-Shaper.vst3`, l'app standalone e `Installa.command`.
Codice plugin `Nshp`, manufacturer `Umsm` (CONTROLUNA): convive con Smoker, non lo sostituisce.
