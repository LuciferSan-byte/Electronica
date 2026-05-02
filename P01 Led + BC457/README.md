# P01 — Tranzistor NPN BC547 + LED

## Descriere
BC547 folosit ca comutator digital.
Buton apăsat → tranzistor în saturație → LED aprins.
Buton liber → tranzistor blocat → LED stins.

## Componente folosite
- BC547 NPN
- LED albastru
- Rezistor R_C = 680Ω (colector)
- Rezistor R_B = 100kΩ (bază)
- Rezistor pull-down 10kΩ (buton)
- Buton

## Date inițiale
- VCC = 9.84V
- V_LED = 3V (albastru)
- I_LED = 10mA = I_C
- h_FE = β = 200
- V_BE = 0.7V
- V_CE(sat) = 0.2V

## Calcule
**R_C = (VCC - V_LED - V_CE) / I_C**
R_C = (9.84 - 3 - 0.2) / 0.01 = 6.64 / 0.01 = 664Ω → 680Ω 

**I_B(min) = I_C / h_FE**
I_B(min) = 10mA / 200 = 0.05mA = 50µA

**R_B = (VCC - V_BE) / I_B**
R_B = (9.84 - 0.7) / 0.00005 = 182kΩ → 100kΩ din stoc

**I_B real = (9.84 - 0.7) / 100,000 = 83µA > 50µA → saturație sigură **

**I_E ≈ I_C = 10mA**

## Măsurători reale
| Parametru | Teoretic | Măsurat |
|-----------|----------|---------|
| V_CE | 0.2V | 0.2V  |
| V_BE | 0.7V | 0.7V  |
| V_RC | 6.63V | 6.6V  |

## Cum funcționează
Buton apăsat → V_B = VCC prin R_B → V_BE = 0.7V →
tranzistor conduce → V_CE = 0.2V → curent prin LED → aprins.
Buton liber → pull-down trage baza la GND →
V_BE = 0V → tranzistor blocat → LED stins.

## Ce am învățat
- Tranzistor NPN ca comutator
- Calcul R_C, R_B, I_B
- V_BE = 0.7V, V_CE(sat) = 0.2V
- Saturație vs blocare
- Pull-down pe buton — pin nu floating
