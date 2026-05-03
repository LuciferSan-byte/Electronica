# P04 — NE555 Astabil ~1Hz

## Descriere
NE555 în mod astabil — oscilator pătrat ~1Hz.
LED clipește vizibil la ~1 clipire pe secundă.
Simulat în LTspice și verificat pe breadboard.

## Componente folosite
- NE555 Timer
- Rezistor R1 = 10kΩ
- Rezistor R2 = 68kΩ
- Condensator C = 10µF electrolitic
- Condensator 68nF pe PIN 5
- LED verde
- Rezistor 680Ω (protecție LED)
- Alimentare 9V

## Calcule
**f = 1.44 / ((R1 + 2×R2) × C)**
f = 1.44 / ((10,000 + 136,000) × 0.00001)
f = 1.44 / 1.46 = **0.986Hz ≈ 1Hz** 

**Duty cycle = (R1 + R2) / (R1 + 2×R2)**
D = 78,000 / 146,000 = **53.4%**

**t_HIGH = 0.693 × (R1 + R2) × C = 0.541s**
**t_LOW = 0.693 × R2 × C = 0.471s**

## Simulare LTspice
- Software: LTspice, .tran 5s
- V_max = 9V, V_min = 0V 
- Perioadă simulată = ~1s 

## Măsurători reale
- 10 clipiri în 10 secunde → **f = 1Hz** 
- Teoretic = real → eroare 0%

## Cum funcționează
Condensatorul se încarcă prin R1+R2 spre 2/3 VCC → PIN 3 HIGH → LED aprins.
La 2/3 VCC → NE555 comută → PIN 7 activat → condensator descarcă prin R2.
La 1/3 VCC → NE555 comută din nou → LED aprins.
Ciclu se repetă la infinit.

Descărcare doar prin R2 → duty cycle > 50% când R1 > 0.
Divizorul intern 3×5kΩ setează pragurile 1/3 și 2/3 VCC.

## Ce am învățat
- NE555 astabil — formula frecvență și duty cycle
- Încărcare prin R1+R2, descărcare prin R2 singur
- Pragurile 1/3 VCC și 2/3 VCC — divizor intern
- PIN 5 necesită condensator ceramic la GND
- Simulare LTspice cu .tran
