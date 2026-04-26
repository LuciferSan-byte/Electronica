# P15 — Arduino + HC-SR04 — Detector Distanță

## Componente folosite
- Arduino Uno
- HC-SR04 senzor ultrasunete
- LED roșu
- Rezistor 330Ω (protecție LED)
- Breadboard + fire

## Calcule
Viteza sunet în aer: 340m/s = 0.0343 cm/µs
Distanța = (durata_echo × 0.0343) / 2
Prag ales: 20cm — obiect detectat sub această distanță

## Cod
(vezi main.cpp)

## Măsurători reale
- Obiect la ~6cm → Serial afișează 6cm 
- Obiect la ~15cm → Serial afișează 15cm 
- Obiect la ~23cm → peste prag, LED stins 

## Ce am învățat
- HC-SR04 măsoară timp dus-întors al ultrasunetului
- pulseIn() cronometrează pulsul ECHO în µs
- delayMicroseconds() vs delay() — precizie µs
- Formula conversie timp → distanță

## Probleme întâlnite
- DHT11 defect → înlocuit cu HC-SR04
- ESP32-C3 Serial CDC probleme → folosit Arduino Uno
