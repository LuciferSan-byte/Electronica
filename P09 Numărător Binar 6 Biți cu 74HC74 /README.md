# P9 — Numărător Binar 6 Biți cu 74HC74

## Componente folosite
- 74HC74 Flip-Flop D x3 (6 FF-D total)
- NE555 Timer — clock ~2Hz
- LED albastru x6
- Rezistor 330Ω x6
- Rezistor R1 = 1kΩ, R2 = 3.3kΩ
- Condensator 100µF
- Arduino 5V ca sursă

## Calcule
f = 1.44 / ((1000 + 2×3300) × 0.0001)
f = 1.44 / 0.76 = ~1.9Hz

## Cum funcționează
D conectat la Q̄ → toggle la fiecare clock.
CLK2 → Q1 → Q2 se schimbă la fiecare 2 clockuri.
CLK3 → Q2 → Q3 se schimbă la fiecare 4 clockuri.
Fiecare FF divide frecvența la 2.
LED-urile conectate la Q̄ — la pornire par toate stinse.

## Secvența de numărare
0→1→2→3→...→63→0 (ciclu complet)

## Măsurători
Funcțional confirmat — pornit 10 minute fără erori ✅

## Probleme întâlnite
- 74HC74 alimentat la 9V → comportament ciudat
  → soluție: 5V de la Arduino
- Fir solid core defect → Q2 nu comuta corect
  → soluție: înlocuit cu fir normal
- LED-uri la Q în loc de Q̄ → numărare inversată
  → soluție: conectat la Q̄
- CLK la Q̄ în loc de Q → secvențe repetate
  → soluție: CLK la Q normal

## Ce am învățat
- FF-D cu D→Q̄ = toggle
- Înlănțuire FF = divizor frecvență binar
- Loading effect pe GPIO → fir defect poate cauza
- PRE/CLR floating → stare aleatorie la pornire
