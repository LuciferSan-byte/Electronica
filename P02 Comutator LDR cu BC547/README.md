# P02 Comutator LDR cu BC547

## Descriere
LDR controlează un LED prin tranzistor BC547.
Întuneric → LED aprins, Lumină → LED stins.

## Componente folosite
- BC547 NPN
- LDR simplu 2 pini
- Rezistor R_div = 100kΩ
- Rezistor R_C = 430Ω
- LED albastru
- Alimentare 9.80V

## Măsurători LDR
- Întuneric total: R_LDR = 500kΩ
- Lumină (flash telefon): R_LDR = 500Ω

## Calcule
**V_B la întuneric:**
V_B = VCC × R_LDR / (R_div + R_LDR)
V_B = 9.80 × 500,000 / (100,000 + 500,000) = **8.17V** 

**V_B la lumină:**
V_B = 9.80 × 500 / (100,000 + 500) = **490mV** 

**R_C = (VCC - V_LED - V_CE) / I_C**
R_C = (9.80 - 3 - 0.2) / 0.015 = 440Ω → **430Ω** din stoc 

**I_B(min) = I_C / h_FE = 15mA / 200 = 75µA**

**I_B real = (V_B - V_BE) / R_div**
I_B = (8.17 - 0.7) / 100,000 = **74µA** ≈ 75µA 

## Măsurători reale
| Parametru | Teoretic | Măsurat |
|-----------|----------|---------|
| V_B întuneric | 8.17V | 8.167V  |
| V_B lumină | 490mV | 480mV |
| V_CE întuneric | 0.2V | 0.2V  |
| I_C | 9mA | 9mA  |

## Cum funcționează
LDR + R_div = divizor de tensiune.
Întuneric → R_LDR mare → V_B mare → BC547 saturație → LED aprins.
Lumină → R_LDR mic → V_B mic → BC547 blocat → LED stins.

## Probleme întâlnite
- R_div = 62kΩ → V_B la lumină = 785mV > 0.7V
  → tranzistor conducea și la lumină!
  → soluție: R_div = 100kΩ
- I_B la limită — h_FE real > 200 salvează situația

## Ce am învățat
- LDR — rezistență variabilă cu lumina
- Divizor de tensiune cu LDR
- Loading effect — R_div acționează și ca R_B
- Alegerea R_div — compromis între V_B și I_B
