# P05 NE555 Monostabil 5s

## Descriere
NE555 în mod monostabil — un singur puls la apăsarea butonului.
LED aprins exact ~5 secunde după apăsare, după care se stinge singur.

## Componente folosite
- NE555 Timer
- Rezistor R = 10kΩ
- Condensator C = 470µF electrolitic
- Condensator 68nF pe PIN 5
- Rezistor pull-up 10kΩ pe PIN 2
- Buton
- LED albastru
- Rezistor 680Ω (protecție LED)
- Alimentare 9V

## Calcule
**t = 1.1 × R × C**
t = 1.1 × 10,000 × 0.00047
t = **5.17 secunde** 

**R = t / (1.1 × C) = 5 / (1.1 × 0.00047) = 9.67kΩ → 10kΩ** 

## Măsurători reale
- Timp măsurat: **~5.3s** 
- Diferența față de teoretic — reacție umană la cronometru

## Cum funcționează
Buton neapăsat → PIN 2 HIGH (pull-up) → NE555 în repaus → LED stins.
Buton apăsat → PIN 2 LOW → sub 1/3 VCC → NE555 declanșează.
PIN 3 → HIGH → LED aprins.
Condensatorul se încarcă prin R spre 2/3 VCC.
La 2/3 VCC → NE555 resetează → PIN 3 LOW → LED stins.
Un singur puls — nu se repetă până la o nouă apăsare.

## Diferența față de astabil
Astabil → oscilează continuu automat.
Monostabil → un singur puls la trigger → se oprește singur.

## Ce am învățat
- NE555 monostabil — formula t = 1.1 × R × C
- Trigger pe frontul negativ — PIN 2 sub 1/3 VCC
- Pull-up obligatoriu pe PIN 2
- PIN 4 (RESET) → VCC obligatoriu
- Un puls fix indiferent cât ții butonul apăsat
