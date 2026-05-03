# P18 Convertor Boost cu BC547 + Bobină

## Descriere
Convertor boost care ridică tensiunea de la 5V la ~10V.
NE555 generează PWM rapid care comută BC547.
Bobina stochează energie și o eliberează la tensiune mai mare.

## Componente folosite
- NE555 Timer (PWM ~18kHz)
- BC547 NPN (comutator)
- Bobină 100µH
- Diodă 1N5817 Schottky
- Condensator 100µF (filtru output)
- Ra = 220Ω, Rb = 10kΩ, C = 68nF (NE555)
- Rezistor bază = 2.7kΩ
- Rezistor emitor = 11Ω (protecție curent)
- Alimentare 5V (Arduino)

## Calcule
**Frecvență NE555:**
f = 1.44 / ((Ra + 2×Rb) × C)
f = 1.44 / ((220 + 20,000) × 0.000000068)
f = **~18kHz** 

**Duty cycle:**
D = (Ra + Rb) / (Ra + 2×Rb) = 10,220 / 20,440 = **50%**

**Tensiune output teoretică:**
V_out = V_in / (1 - D) = 5 / (1 - 0.5) = **10V** 

**Protecție curent emitor:**
I_max = V_BE / R_E = 0.7 / 11 = **~63mA** < 100mA 

## Măsurători reale
- V_input = 5V (Arduino)
- V_output = **10V** 
- Boost factor = 2x 

## Cum funcționează
NE555 → semnal PWM 18kHz → comută BC547 rapid.
BC547 ON → curent crește prin bobină → energie stocată în câmp magnetic.
BC547 OFF → bobina împinge curent înainte → tensiune mare → diodă → condensator.
Condensatorul netezește output → DC stabil la 10V. 

## De ce Schottky 1N5817
- Cădere tensiune 0.3V vs 0.7V la 1N4007
- Recuperare rapidă → esențial la 18kHz
- 1N4007 prea lentă la frecvențe mari

## Probleme întâlnite
- BC547 s-a ars la prima încercare
  → cauza: curent de vârf prea mare fără protecție
  → soluție: rezistor 11Ω pe emitor + Rb mai mare
- NE555 output = 4V (nu 5V)
  → normal — pierderi interne la 5V alimentare

## Ce am învățat
- Principiul convertorului boost
- Bobina se opune schimbării curentului
- V_out = V_in / (1 - D)
- De ce frecvență mare → bobină mică
- Protecție curent obligatorie pentru BC547
- Diodă Schottky pentru comutare rapidă
