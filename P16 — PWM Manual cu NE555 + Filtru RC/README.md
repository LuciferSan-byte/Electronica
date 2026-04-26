# P16 — PWM Manual cu NE555 + Filtru RC

## Componente folosite
- NE555 Timer
- Potențiometru 10kΩ
- Diodă 1N4007
- Rezistor R1 = 1kΩ
- Condensator timing = 68nF ceramic
- Rezistor filtru = 1kΩ
- Condensator filtru = 1µF electrolitic
- Rezistor LED = 680Ω
- LED albastru

## Calcule
f = 1.44 / ((R1 + 2×R2) × C)
f = 1.44 / (21000 × 0.000000068) = ~1kHz

τ filtru = R × C = 1000 × 0.000001 = 0.001s
T semnal = 1/1000 = 0.001s
τ > T 

Duty cycle variabil: 0% → 100% cu diodă în paralel

## Cum funcționează
NE555 produce semnal pătrat cu frecvență ~1kHz.
Potențiometrul controlează duty cycle.
Dioda separă calea de încărcare de cea de descărcare
→ duty cycle variabil 0-100%.
Filtrul RC transformă PWM în tensiune DC:
V_DC = duty_cycle × VCC
Tensiunea DC controlează luminozitatea LED-ului.

## Măsurători reale
- Potențiometru maxim → V_DC ≈ 0V → LED stins
- Potențiometru minim → V_DC ≈ VCC → LED aprins

## Probleme întâlnite
- PIN 7 neconectat la VCC → NE555 nu oscila
- Scurtcircuit pe breadboard → debugging lung
- PIN 5 fără condensator → comportament instabil
- Fără diodă → variație duty cycle doar 52%-100%
- Condensator timing prea mare → frecvență vizibilă

## Ce am învățat
- PWM = Pulse Width Modulation — duty cycle variabil
- Filtru RC transformă PWM în DC
- V_DC = duty_cycle × VCC
- Dioda separă încărcare/descărcare în NE555
- PIN 5 necesită condensator la GND întotdeauna
