# P03 Histerezis cu BC547 + Feedback Rezistiv

## Descriere
Circuit LDR cu histerezis — două praguri diferite de comutare.
Întuneric → LED aprins, Lumină → LED stins.
Feedback rezistiv între colector și bază previne flicker-ul.

## Componente folosite
- BC547 NPN
- LDR simplu 2 pini
- Rezistor R_div = 1MΩ
- Rezistor R_C = 430Ω
- Rezistor R_f = 1MΩ (feedback colector→bază)
- LED albastru
- Alimentare 9.80V

## Calcule
**V_B la lumină (R_LDR = 500Ω):**
V_B = 9.8 × 500 / (1,000,000 + 500) = **6mV** 
→ 6mV << 700mV → tranzistor blocat → LED stins

**V_B la întuneric (R_LDR = 500kΩ):**
V_B = 9.8 × 500,000 / (1,000,000 + 500,000) = **3.26V** 
→ 3.26V >> 700mV → tranzistor saturație → LED aprins

**Curent feedback:**
I_f = (VCC - V_BE) / R_f = (9.8 - 0.7) / 1,000,000 = **9.1µA**
Foarte mic — nu perturbă circuitul 

## Măsurători reale
| Parametru | Teoretic | Măsurat |
|-----------|----------|---------|
| V_B lumină | 6mV | 6mV  |
| V_B întuneric | 3.26V | 3.3V  |
| V_CE întuneric | 0.2V | 0.2V |
| Histerezis | vizibil | confirmat  |

## Cum funcționează histerezisul
R_f conectat între colector și bază:

**LED aprins** → V_C = 0.2V → R_f trage baza în jos
→ prag de oprire coborât → trebuie mai multă lumină să stingă

**LED stins** → V_C = 9.8V → R_f injectează curent în bază
→ prag de pornire ridicat → trebuie mai mult întuneric să aprindă

Rezultat: **două praguri diferite** → nu mai există flicker! 

## Probleme întâlnite
- R_div = 100kΩ → V_B lumină = 480mV — prea aproape de 700mV
  → histerezis îngust, LED slab aprins la lumină
  → soluție: R_div = 1MΩ
- R_f = 100kΩ → curent feedback prea mare
  → LED aprins slab la lumină
  → soluție: R_f = 1MΩ

## Ce am învățat
- Histerezis — două praguri de comutare diferite
- Feedback rezistiv colector→bază
- De ce R_div trebuie mult mai mare decât R_LDR(lumină)
- R_f >> R_C pentru a nu perturba circuitul
- Flicker eliminat prin histerezis
