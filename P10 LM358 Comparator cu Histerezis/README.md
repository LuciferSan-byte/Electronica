# P10 LM358 Comparator cu Histerezis

## Descriere
LM358 Op-Amp folosit ca comparator de tensiune cu histerezis.
LDR ca senzor de lumină — întuneric → LED aprins, lumină → LED stins.
Histerezis prin feedback rezistiv pe intrarea neinversoare.

## Componente folosite
- LM358 Op-Amp
- LDR simplu 2 pini
- Rezistor R_fix = 100kΩ (divizor LDR)
- Rezistor R1 = 20kΩ (referință)
- Rezistor R2 = 10kΩ (referință)
- Rezistor R_feedback = 100kΩ
- Rezistor 680Ω (protecție LED)
- LED albastru
- Alimentare 9V

## Calcule

**Tensiune referință V+:**
V_ref = VCC × R2 / (R1 + R2)
V_ref = 9 × 10,000 / (20,000 + 10,000) = **3V** 

**V- la întuneric (R_LDR = 500kΩ):**
V- = 9 × 100k / (500k + 100k) = **1.5V** 
1.5V < 3V → V+ > V- → ieșire HIGH → LED aprins 

**V- la lumină (R_LDR = 500Ω):**
V- = 9 × 100k / (500 + 100k) = **~8.9V** 
8.9V > 3V → V+ < V- → ieșire LOW → LED stins 

## Conexiuni
- PIN 8 (VCC) → 9V
- PIN 4 (GND) → GND
- PIN 2 (V-) → nod LDR/R_fix
- PIN 3 (V+) → nod R1/R2 + R_feedback
- PIN 1 (OUT) → 680Ω → LED → GND
- LDR → VCC, R_fix (100kΩ) → GND
- R_feedback (100kΩ) între PIN 1 și PIN 3

## Cum funcționează
Op-Amp compară V+ și V-:
- V+ > V- → ieșire HIGH → LED aprins
- V+ < V- → ieșire LOW → LED stins

Histerezis: R_feedback modifică V+ în funcție de starea ieșirii:
- Ieșire HIGH → feedback ridică V+ → prag de oprire mai sus
- Ieșire LOW → feedback coboară V+ → prag de pornire mai jos
Rezultat: două praguri diferite → fără flicker! 

## Avantaj față de BC547
- Impedanță intrare Op-Amp = MΩ → nu perturbă divizorul
- Tensiune de referință precisă și stabilă
- Comutare mai clară și mai rapidă

## Ce am învățat
- LM358 ca comparator
- Histerezis cu Op-Amp — feedback pe V+
- Impedanță mare intrare Op-Amp vs tranzistor
- Diferența comparator inversor vs neinversor
- LM358: 3V - 32V, funcționează la 9V 
