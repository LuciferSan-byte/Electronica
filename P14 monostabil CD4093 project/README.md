# P14 — Monostabil Retriggerable cu CD4093BE

## Descriere
Circuit care produce un puls de 3.6s la apăsarea 
unui buton. Retriggerable — o nouă apăsare 
resetează timerul.

## Componente
- CD4093BE (1x poartă NAND Schmitt-trigger)
- Rezistor 20kΩ + 10kΩ în serie (R = 30kΩ)
- Condensator electrolitic 100µF
- LED albastru
- Rezistor 680Ω (protecție LED)
- Buton

## Calcule
t = 1.2 × R × C
t = 1.2 × 30000 × 0.0001 = 3.6s

## Măsurători reale
Timp măsurat: ~3.6s 

## Cum funcționează
Buton apăsat → condensator descărcat la GND → 
intrare LOW → ieșire HIGH → LED aprins.
Condensatorul se încarcă prin R spre VCC.
Când tensiunea ajunge la V_T+ → ieșire LOW → 
LED stins.

## Probleme intalnite 
Am asamblat circuitul cu un condensator care nu mai facea conexiunea cu piciorusele 
asa ca led ul statea mereu stins 

## Alimentare
9V baterie
