# P11 — Oscilator RC cu CD4093BE

## Descriere
Oscilator pătrat folosind o singură poartă NAND Schmitt-trigger
din CD4093BE și componente RC.
LED clipește vizibil la ~8.33Hz.

## Componente folosite
- CD4093BE (1x poartă NAND Schmitt-trigger)
- Rezistor R = 10kΩ
- Condensator C = 10µF electrolitic
- LED albastru
- Rezistor 680Ω (protecție LED)
- Alimentare 9V

## Calcule
**f = 1 / (1.2 × R × C)**
f = 1 / (1.2 × 10,000 × 0.00001)
f = 1 / 0.12 = **8.33Hz** 

**R_LED = (VCC - V_LED) / I_LED**
R_LED = (9 - 2) / 0.01 = 700Ω → 680Ω din stoc 

## Conexiuni
- Ieșire poartă → R (10kΩ) → Nod
- Nod → Intrări A și B (împreună)
- Nod → C (10µF) → GND
- Ieșire → 680Ω → LED → GND

## Măsurători reale
- 10 clipiri în 1.2s → f = 10/1.2 = **8.33Hz** 
- Teoretic = real → 0% eroare

## Cum funcționează
Ieșire HIGH → condensator se încarcă spre VCC.
Tensiune ajunge la V_T+ → ieșire comută LOW.
Condensator se descarcă spre V_T-.
Tensiune ajunge la V_T- → ieșire comută HIGH.
Ciclu se repetă la infinit → oscilație! 

Histerezisul Schmitt-trigger menține oscilația stabilă —
o poartă normală s-ar bloca la tensiunea de comutare.

## Ce am învățat
- Oscilator Schmitt-trigger RC
- Formula f = 1/(1.2×R×C)
- De ce histerezisul e necesar pentru oscilație
- CD4093 suportă până la 18V 
