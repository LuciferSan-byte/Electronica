# P21 Ceas Digital cu Alarmă și Melodie
## Componente folosite
- Display 7 segmente 4 cifre common anode
- 11x BC547 NPN (7 segmente + 4 cifre comune)
- Arduino Uno
- 4x butoane + 4x rezistoare pull-down 10kΩ
- Buzzer pasiv
- Rezistoare: 430Ω x7 (segmente), 10kΩ x11 (bază + pull-down), 2.7kΩ x4 (bază pini comuni)
- Alimentare: 5V de la USB
## Calcule
- Rc segment = (Vcc - Vce - Vf) / If = (5 - 0.2 - 1.8) / 0.007 = 430Ω
- Rb segment = 10kΩ → Ib = 0.43mA → saturație ok
- Rb pini comuni = 2.7kΩ → Ib = 1.6mA pentru Ic max = 49mA
- Frecvență multiplexare: 4 cifre × 3ms = ~83Hz refresh
## Funcționalități
- Afișare HH:MM cu multiplexare software
- 4 butoane: oră, minute, mod alarmă, oprire alarmă
- Debouncing 200ms cu millis()
- EEPROM save pentru ceas (la fiecare minut) și alarmă
- Buzzer cu melodie non-blocking "Lion Sleeps Tonight"
- Melodia se reia în buclă până la oprire
## Probleme întâlnite
tranzistor ars am adaugat rezistenta in emitor 
ghoasting am stins butoanele inainte sa le apridna iarasi ca sa nu mai apara fenomenul 
buzzer ul continua sa scoata sunet l am oprit dupa ce am oprti si melodia 
## Ce am învățat
cum sa repar ghosting
EEPROM pe arudino
cum sa fac m,eldoii cu buzzer 
cum sa fac mulipelxare cu mllis
