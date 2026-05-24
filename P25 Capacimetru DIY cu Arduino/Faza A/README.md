# P25 Capacimetru DIY cu Arduino (Faza A)

## Descriere proiect

Capacimetru construit cu Arduino Uno care măsoară capacitatea unui condensator prin metoda RC charging. Folosește un rezistor de referință cunoscut și măsoară timpul în care condensatorul ajunge la 63.2% din tensiunea de alimentare (= 1τ). Rezultatul este afișat pe un LCD 1602.

Faza A este versiunea minimă, cu un singur rezistor de referință, fără auto-range. Acoperă range-ul ~10 nF - 300 µF.

## Componente folosite

- 1 x Arduino Uno
- 1 x LCD 1602 (HD44780, fără modul I2C, conectare 4-bit)
- 1 x Potențiometru 10 kΩ (pentru contrast LCD)
- 1 x Rezistor de referință 10 kΩ (valoare măsurată: 9890 Ω cu multimetru)
- 1 x Rezistor 220 Ω (limitare curent backlight LCD)
- 1 x breadboard
- Fire solid-core 22 AWG

## Arhitectura circuitului

### Etaj 1 - Conexiuni LCD parallel (modul 4-bit)

| LCD pin | Arduino pin | Rol |
|---------|-------------|-----|
| 1 (Vss) | GND | Masa |
| 2 (Vdd) | +5V | Alimentare logic |
| 3 (Vo) | wiper potențiometru | Contrast |
| 4 (RS) | D4 | Register Select |
| 5 (R/W) | GND | Mereu scris |
| 6 (E) | D6 | Enable |
| 11 (DB4) | D10 | Data bit 4 |
| 12 (DB5) | D11 | Data bit 5 |
| 13 (DB6) | D12 | Data bit 6 |
| 14 (DB7) | D13 | Data bit 7 |
| 15 (V+ backlight) | +5V prin 220Ω | Backlight + |
| 16 (V- backlight) | GND | Backlight - |

### Etaj 2 - Circuit capacimetru

- D8 (charge) -> Rfix (9890 Ω) -> nod -> Cx (condensator de testat) -> GND
- D9 (discharge) -> direct la nod (fără rezistor)
- A0 (sense) -> direct la nod (citire ADC)

## Principiul de funcționare

### Formula RC charging

Tensiunea pe condensator în funcție de timp:

V(t) = Vcc * (1 - e^(-t/RC))

La momentul t = τ = R * C, tensiunea ajunge la 63.2% din Vcc. Asta este definiția matematică a constantei de timp.

### Algoritmul de măsurare

1. **Descărcare:** D9 = OUTPUT LOW, D8 = INPUT. Cx se descarcă prin D9 direct la GND (rapid). Timeout 100 ms.
2. **Verificare descarcat:** ADC < 50 confirmă descărcarea completă.
3. **Pornire încărcare:** D9 = INPUT, D8 = OUTPUT HIGH. Cx se încarcă prin Rfix.
4. **Pornire cronometru:** micros() la momentul pornirii.
5. **Loop citire ADC:** până ADC depășește pragul 647 (= 63.2% din 1023).
6. **Stop cronometru:** salvăm timpul scurs τ.
7. **Calcul Cx:** Cx = τ / Rfix
8. **Detectie auto-range pentru afișaj:** µF / nF / pF în funcție de magnitudine.
9. **Afișare LCD** cu unitate corectă.

### Detectie "No Cap"

Două mecanisme:
- **La descărcare:** dacă ADC nu scade sub 50 în 100 ms timeout, afișează "No Cap".
- **La încărcare:** dacă timpul depășește 3 secunde, afișează "No Cap / OOR" (Out Of Range).

### Detectie polaritate

Pentru electrolitice, atenție polaritate. Catodul (-) la GND, anodul (+) la nod.

## Calcule

### Pragul ADC 63.2%

Prag ADC = 1023 × 0.632 = 646.5 ≈ **647**

Independent de Vcc - lucrăm cu raport, nu cu tensiune absolută.

### Rezoluție timing

micros() pe Arduino Uno: rezoluție 4 µs.

Pentru τ = 100 µs, eroare timing = 4%.
Pentru τ = 1 ms, eroare timing = 0.4%.
Pentru τ = 10 ms, eroare timing = 0.04%.

### Range util

| Cx | τ teoretic | Precizie estimată |
|------|------------|-------------------|
| 1 nF | 10 µs | ±50% (sub rezoluție timing + parazite) |
| 10 nF | 100 µs | ±15-20% |
| 100 nF | 1 ms | ±5-10% |
| 1 µF | 10 ms | ±5% |
| 10 µF | 100 ms | ±5% |
| 100 µF | 1 sec | ±5% |
| 300 µF | 3 sec | ±10% (la limita timeout) |
| 470 µF | 4.7 sec | Out of range (depășește timeout) |

## Măsurători reale

| Cx nominal | Cx măsurat | Eroare |
|------------|------------|--------|
| 33 µF (electrolitic) | 34.3 µF | +3.9% |
| 100 µF (electrolitic) | 102.4uf | +2.4% |

Toleranța componentelor: ±20% pentru ceramice și electrolitice din stoc.

## Limitări observate

### 1. Capacități parazite la valori mici

Pentru Cx sub 10 nF, capacitățile parazite ale breadboard-ului, firelor și pinilor Arduino (aprox 50-100 pF) contribuie semnificativ la măsurătoare. Eroarea crește la peste 20%.

**Soluție viitoare:** calibrare prin scăderea capacității parazite măsurate fără condensator, sau utilizarea unui R_ref mai mare (1 MΩ) în Faza B pentru a deplasa range-ul util spre valori mici.

### 2. Range maxim limitat de timeout

3 secunde timeout permite măsurarea până la ~300 µF. Condensatoare mai mari (470 µF, 1000 µF) depășesc timeout-ul.

**Soluție viitoare:** Rref mai mic (1 kΩ) în Faza B pentru a deplasa range-ul util spre valori mari.

### 3. Calibrare absolută

Capacimetrul folosește valoarea măsurată a R_ref (9890 Ω) ca referință absolută. Precizia finală depinde de precizia multimetrului folosit pentru măsurare R_ref.

### 4. Toleranță componente

Condensatorii folosiți (ceramic și electrolitic) au toleranță ±20%. Capacimetrul detectează corect valoarea reală, dar nu poate verifica dacă valoarea marcată e corectă.

## Ce am învățat

- Principiul RC charging și constanta de timp τ
- Formula V(t) = Vcc * (1 - e^(-t/RC)) și proprietatea la 63.2%
- Cum se controlează 2 pini Arduino pentru charge/discharge fără short circuit
- pinMode INPUT vs OUTPUT (high impedance vs activ)
- Utilizare micros() pentru timing precis (vs millis())
- ADC threshold detection (compararea cu prag fix 647)
- LCD parallel HD44780 conectare în mod 4-bit
- Bibliotecă LiquidCrystal Arduino
- Float arithmetic în Arduino (împărțire cu zecimală)
- Auto-detectare unitate (pF / nF / µF) pentru afișaj
- Detectie "No Cap" la descărcare și la încărcare

## Cod

Fragment esențial:

```cpp
// Algoritmul principal de măsurare
unsigned long incarcare() {
    unsigned long timpIncarcare = micros();
    pinMode(charge, OUTPUT);
    pinMode(disCharge, INPUT);
    digitalWrite(charge, HIGH);
    
    while (analogRead(masurare) < 647) {
        if (micros() - timpIncarcare > 3000000) {
            return 0;  // timeout sau no cap
        }
    }
    return micros() - timpIncarcare;
}

// Calcul capacitate
float capacitate = (timpMicros / 1000000.0) / Rfix;
```

## Foto

![Schema breadboard](./poze/breadboard.jpeg)
![Capacimetru măsurând 33µF](./poze/test_33uF.jpeg)
![Detectie No Cap](./poze/no_cap.jpeg)

## Roadmap evoluție

### Faza A (curent) - Versiune minimă
- 1 rezistor de referință (10 kΩ)
- Range 10 nF - 300 µF
- Detectie No Cap
- Afișaj LCD cu auto-detectare unitate

### Faza B - Auto-range
- 3-4 rezistoare de referință (1 MΩ, 100 kΩ, 10 kΩ, 1 kΩ)
- Selecție automată R_ref în funcție de range Cx
- Range extins: 1 nF - 3 mF
- Calibrare prin scăderea capacității parazite

### Faza C - Versiune avansată
- Auto-range hardware cu MOSFET-uri 2N7000 (din stoc)
- Detectie polaritate (electrolitic vs ceramic)
- Comparare cu valori standard E12 / E24
- Eventual buton pentru declanșare manuală
- Stocare ultimele 10 măsurători pentru sortare
