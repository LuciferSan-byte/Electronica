# P24 Voltmetru DIY 0-30V cu Arduino

## Descriere proiect

Voltmetru cu range 0-30V, construit cu ajutorul unui Arduino Uno, prin citirea tensiunii de la pinul A0 cu comanda `analogRead()`. Tensiunea de intrare este redusă printr-un divizor rezistiv 1/6, izolată de ADC printr-un buffer LM358, iar valoarea finală este afișată pe un display 7-segment cu 4 cifre.

## Componente folosite

- 1 × Arduino Uno
- 1 × LM358 (folosit ca buffer voltage follower, 1 op-amp din 2)
- 4 × Display 7-segment (catod comun)
- 4 × Tranzistor BC547 (drivere multiplexare digit-uri)
- 4 × Rezistor 1kΩ (bază BC547)
- 7 × Rezistor 330Ω (segmente)
- Rezistoare divizor: 1 × 100kΩ (R1), 1 × 20kΩ (R2)
- 1 × Rezistor pull-down 5.6MΩ (pe nodul divizorului)
- 2 × breadboard
- Fire solid-core 22 AWG

## Arhitectura circuitului

### Etaj 1 — Divizor de tensiune

- R1 = 100kΩ (de la intrare la nodul divizorului)
- R2 = 20kΩ (de la nod la GND)
- Raport: 1/6 (transformă 0-30V la intrare în 0-5V la nod)
- Rechivalent (paralel) = 16.7kΩ
- Curent la 30V: 30V / 120kΩ = 250 µA

**De ce raport 1/6 și valorile astea:**

Range-ul de intrare dorit e 0-30V, iar ADC Arduino acceptă maxim 5V. Raportul minim necesar = 30/5 = 6. Cu R1 = 100kΩ și R2 = 20kΩ, raportul e exact 1/6. Valorile sunt suficient de mari pentru a nu trage curent semnificativ din sursa măsurată (250 µA la 30V), dar și suficient de mici pentru ca eroarea cauzată de bias current-ul LM358 să fie neglijabilă.

### Etaj 2 — Pull-down

- Rezistor 5.6MΩ între nodul divizorului și GND
- Rol: când nimic nu e conectat la intrare, ține nodul la 0V (afișaj stabil)
- Impact pe raport divizor: neglijabil (R2 || 5.6M ≈ 20kΩ)

### Etaj 3 — Buffer LM358

- Pin 3 (IN+) = nodul divizorului
- Pin 2 (IN−) = pin 1 (OUT), feedback direct = voltage follower
- Pin 8 (Vcc) = +5V Arduino
- Pin 4 (GND) = GND Arduino
- Pin 1 (OUT) = A0 Arduino
- Rol: izolează divizorul de ADC, impedanță mare de intrare, mică de ieșire

### Etaj 4 — Arduino Uno + ADC

- A0 citește output buffer
- ADC pe 10 biți → 0-1023 valori pentru 0-5V
- Rezoluție efectivă la circuit: ~30 mV per LSB

### Etaj 5 — Display 7-segment multiplexat

- 4 cifre cu zecimală (XX.XX)
- Multiplexare cu BC547 ca drivere pentru fiecare digit
- Refresh la 2 ms per cifră (125 Hz total)

## Calcule

### Divizor de tensiune

| Parametru | Valoare |
|-----------|---------|
| R1 | 100 kΩ |
| R2 | 20 kΩ |
| Raport (R2 / (R1+R2)) | 1/6 = 0.1667 |
| Tensiune max input | 30 V |
| Tensiune max nod | 5 V |
| Curent la 30V | 250 µA |
| R_echivalent | 16.7 kΩ |

### Rezoluție ADC

- ADC 10 biți → 1024 valori
- Vref efectiv = ~4.66V (Vcc Arduino real, măsurat)
- Rezoluție la pin = 4.66V / 1024 ≈ 4.55 mV
- Rezoluție la circuit (×6) ≈ 27 mV per LSB

### Eroare bias LM358

- Ibias tipic = 45 nA
- ΔV = Ibias × Rechiv = 45 nA × 16.7 kΩ = 0.75 mV
- **Sub rezoluția ADC → invizibil în afișaj**

## Calibrare

Voltmetrul este calibrat folosind tensiunea pe care o scoate Arduino-ul (Vcc) ca referință pentru ADC. În cod, variabila `VREF` trebuie setată la valoarea reală a Vcc-ului Arduino (măsurată cu un multimetru de referință la bornele +5V și GND). Dacă alimentarea Arduino se schimbă (alt cablu USB, altă sursă), VREF trebuie reajustată în cod și firmware-ul reîncărcat.

Un upgrade viitor ar fi auto-calibrarea prin funcția `readVcc()` care folosește referința internă de 1.1V a microcontrolerului pentru a determina Vcc-ul real în timp real.

## Măsurători reale

| Sursă | Multimetru comercial | Voltmetru DIY | Eroare |
|-------|----------------------|---------------|--------|
| +5V Arduino | 4.63 V | 4.64 V | ~10 mV |
| Sursă ~7V | 7.20 V | 7.23 V | ~30 mV |

## Limitări observate

### 1. Loading effect pe surse cu impedanță mare

Voltmetrul are impedanță de intrare ~120kΩ (sumă R1 + R2). Pentru surse cu curent limitat (de ex. multiplicatorul Cockcroft-Walton P23, ~14 µA max), voltmetrul trage prea mult curent și **prăbușește sursa**.

Test concret: multiplicatorul P23 dă 30V în gol, dar scade la ~7V când e conectat voltmetrul DIY.

**Soluții posibile (viitoare):**
- Op-amp cu FET-input (TL072) → permite divizor cu R total în MΩ
- Multimetru comercial pentru astfel de surse (10MΩ impedanță)

### 2. Calibrare manuală

VREF în cod presupune Vcc Arduino fix (4.66V). Schimbarea cablului USB sau a sursei de alimentare necesită recalibrare manuală.

**Soluție viitoare:** funcția `readVcc()` cu referința internă 1.1V pentru auto-calibrare.

### 3. Precizie ADC

Rezoluție efectivă ~27 mV per LSB → ultima zecimală a afișajului poate fluctua cu ±1-2 unități. Acceptat pentru voltmetru didactic.

### 4. Vcc-ul Arduino fluctuant sub sarcină

Display-ul 7-segment multiplexat + LM358-ul trag curent semnificativ de la Arduino. Asta poate cauza Vcc-ul să fluctueze cu ~50-100 mV, ceea ce afectează precizia măsurătorilor. Pentru precizie maximă, Arduino-ul ar trebui alimentat printr-o sursă stabilă (baterie 9V la pin VIN, regulator extern, etc.), nu doar prin USB.

## Ce am învățat

- ADC pe 10 biți și rezoluție per LSB
- Tensiune de referință pentru ADC (Vcc-dependent)
- Voltage divider + loading effect
- Op-amp buffer (voltage follower) izolare impedanță
- Input bias current și eroarea pe Rechivalent
- Filtrare prin medie pentru reducere zgomot
- Pull-down resistor pentru intrare flotantă
- Multiplexare display 7-segment (recapitulare din P21)
- Calibrare instrument vs referință absolută
- Impactul Vcc-ului instabil asupra preciziei ADC

## Foto

![Voltmetru funcțional — comparație cu multimetru](./poze/voltmetru.jpeg)
