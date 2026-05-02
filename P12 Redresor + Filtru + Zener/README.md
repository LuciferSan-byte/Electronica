# P12 Redresor Semipundă + Filtru + Zener

## Descriere
Circuit care transformă un semnal pătrat AC în DC stabilizat.
NE555 astabil simulează sursa AC.
1N4007 redresează, condensator filtrează, Zener stabilizează.

## Componente folosite
- NE555 Timer (astabil ~100Hz)
- Diodă 1N4007 (redresare)
- Condensator electrolitic ≥10µF (filtru)
- Rezistor 430Ω (protecție Zener)
- Diodă Zener 3.3V (stabilizare)
- R1 = 1kΩ, R2 = 6.8kΩ, C = 1µF (NE555)

## Calcule NE555
**f = 1.44 / ((R1 + 2×R2) × C)**
f = 1.44 / ((1000 + 13600) × 0.000001)
f = 1.44 / 0.0146 = **~98.6Hz** 

**Duty cycle = t_high / (t_high + t_low)**
t_high = 0.693 × (R1+R2) × C = 0.0056s
t_low = 0.693 × R2 × C = 0.0047s
Duty cycle = 0.0056/0.0103 = **54%** 

## Calcule Zener
**V_in după 1N4007 = VCC - 0.7V = ~7.3V**
**R_zener = (V_in - V_zener) / I_zener**
R = (7.3 - 3.3) / 0.01 = 400Ω → 430Ω din stoc 

**I_max Zener = P_max / V_zener = 0.5W / 3.3V = 151mA**
I folosit = 10mA → foarte safe 

## Măsurători reale
- Baterie: 8V (descărcată)
- Fără Zener: 6.47V
- Cu Zener 3.3V: **2.91V** 
- Diferență față de teoretic — baterie descărcată

## Cum funcționează
NE555 → semnal pătrat 0-8V
1N4007 → blochează descărcarea condensatorului prin NE555
Condensator → netezește ripple-ul
Zener → stabilizează tensiunea la 3.3V fix

## Rolul diodei 1N4007
Izolează condensatorul — împiedică descărcarea
înapoi prin NE555 când ieșirea e LOW.

## Ce am învățat
- Redresor semipundă
- Filtru RC — τ >> T pentru ripple mic
- Diodă Zener în polarizare inversă
- Rezistor de protecție Zener obligatoriu
- Duty cycle NE555 și tensiune medie
