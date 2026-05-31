

# P25 Capacimetru DIY cu Arduino (Faza B - Auto-range)

## Descriere proiect

Faza B extinde capacimetrul din Faza A cu **auto-range hardware** folosind 4 rezistoare de referință în paralel, fiecare cu pin Arduino propriu. Logica auto-range alege automat rezistorul potrivit în funcție de mărimea condensatorului testat, extinzând range-ul util la **~180 pF - ~1 mF** (vs 10 nF - 300 µF la Faza A).

În plus, codul a fost rescris pentru:
- **Port manipulation directă** pe registrele DDRD/PORTD (atomic switching între rezistoare)
- **Configurare ADC manuală** prin registre (ADMUX, ADCSRA) în loc de analogRead
- **Averaging** pe mai multe măsurători pentru precizie statistică
- **Corecție loading effect** pentru rezistorul mare (1.1MΩ)
- **Calibrare capacitate parazită** prin măsurare empirică

## Componente folosite (în plus față de Faza A)

- 3 x rezistoare suplimentare: 1 kΩ, 100 kΩ, 1.1 MΩ (valori măsurate: 974 Ω, 99100 Ω, 1000000 Ω)
- 1 x rezistor 220 Ω (limitare curent discharge)
- LCD mutat pe alți pini (eliberare Port D pentru atomic switching)

Restul componentelor identice cu Faza A.

## Arhitectura circuitului (Faza B)

### Eliberare Port D - mutare LCD

Pentru a putea folosi 4 pini consecutivi pe Port D pentru rezistoare (D4-D7), LCD-ul a fost mutat:

| Funcție | Pin vechi (Faza A) | Pin nou (Faza B) |
|---------|-------------------|------------------|
| LCD RS | D4                 | **D8** |
| LCD E | D6                  | **D9** |
| LCD D4-D7 | D10-D13         | D10-D13 (neschimbat) |

### Pinout final Faza B

| Funcție | Pin | Detalii |
|---------|-----|---------|
| R1 = 974 Ω | D4 | Port D, bit 4 |
| R2 = 9840 Ω | D5 | Port D, bit 5 |
| R3 = 99100 Ω | D6 | Port D, bit 6 |
| R4 = 1 MΩ | D7 | Port D, bit 7 |
| Discharge | D3 | Prin 220 Ω limitare curent (~22 mA) |
| Sense | A0 | ADC manual, prescaler 128 |
| LCD RS / E | D8 / D9 | Port B |
| LCD D4-D7 | D10-D13 | Port B |

### Schema conceptuală

```
                     +5V
                       |
D4 ---[R1 = 974Ω]------+
D5 ---[R2 = 9.84kΩ]----+
D6 ---[R3 = 99.1kΩ]----+--- nod --- Cx --- GND
D7 ---[R4 = 1.0MΩ]-----+         |
                                 A0 (sense)
                                 |
D3 ---[220Ω]---------------------+ (discharge prin rezistor pentru limitare curent)
```

Logica: doar **UN** pin OUTPUT HIGH la un moment dat (rezistorul activ). Ceilalți pini configurați ca INPUT (high-impedance, practic "deconectați"). Trecerea între rezistoare se face cu o singură operație atomică pe registrele DDRD/PORTD.

## Principiul de funcționare (Faza B)

### Algoritm hibrid: probing rapid + măsurătoare finală

**Etapa 1 - Probing (5 ms per iterație, max 3 iterații)**

Start cu R3 = 99.1 kΩ (mijloc geometric al range-ului). Se activează rezistorul, se așteaptă fix 5 ms, se citește V_ADC.

Decizie pe baza valorii citite:
- **V_ADC între 100 și 920** → rezistorul curent e potrivit pentru această capacitate, treci la măsurătoarea finală
- **V_ADC > 920** → condensatorul s-a încărcat prea repede (C prea mic pentru R curent) → sari la R următor (mai mare)
- **V_ADC < 100** → condensatorul s-a încărcat prea încet (C prea mare pentru R curent) → sari la R precedent (mai mic)
- La extremele range-ului (R = 1 kΩ sau R = 1.1 MΩ), acceptă rezultatul chiar dacă e la limită

**Etapa 2 - Măsurătoare finală cu averaging**

5 măsurători succesive de încărcare cu rezistorul optim ales:
- Pornește încărcarea (port manipulation atomic)
- Cronometrează cu micros() până ADC ≥ 647 (= 63.2% Vcc)
- Aplică timeout adaptiv (1.5 s pentru R = 1 kΩ, 200 ms pentru celelalte)
- Discharge complet între măsurători

Mediază cele 5 valori valide (filtrând eventualele timeout-uri). Necesită minim 3 măsurători reușite, altfel afișează "Out of range".

### Corecție loading effect (doar pentru R = 1.1 MΩ)

Pinul A0 are impedanță de intrare ~100 MΩ. Cu R = 1.1 MΩ se formează un divizor de tensiune care atenuează semnalul cu factor 100/(100+1.1) ≈ 0.989. Asta înseamnă că pentru a vedea 63.2% Vcc real pe ADC, condensatorul trebuie să atingă o tensiune ușor mai mare → tau măsurat ușor mai mare → C calculat mai mare.

Corecție aplicată: `capacitate /= 1.011` (factor invers).

Pentru R = 100 kΩ și mai mici, eroarea de loading e sub 0.1% și se ignoră.

### Calibrare capacitate parazită

Sistemul fizic (breadboard, fire, pini Arduino, capacități parazitare ADC) introduce o **capacitate parazită constantă** care apare ca offset la măsurători. Pentru a o caracteriza:

1. Capacimetrul rulat în gol (nimic conectat la nod)
2. Probing alege automat R = 1.1 MΩ (cel mai sensibil la capacități mici)
3. Loop pe 205 iterații, fiecare cu media a 100 măsurători individuale
4. Media stabilizată: **C_PARAZIT = 205.735 pF**

Această valoare e scăzută din rezultatul final, **doar când probing alege R = 1.1 MΩ**:

```cpp
if (indexRezistenta == 3) {
    capacitate /= 1.011;          // loading correction
    capacitate -= C_PARAZIT;       // scădere capacitate parazită
    if (capacitate < 3e-12) {
        afișează "No cap / < 3pF";
    }
}
```

Pragul de **3 pF** sub care valoarea e considerată zgomot (incertitudinea totală a calibrării + zgomot ADC + drift termic ≈ 1-2 pF).

## Optimizări tehnice

### Port manipulation directă (DDRD / PORTD)

În loc de `digitalWrite()` care durează ~5 µs și nu poate schimba mai mulți pini atomic, folosim accesul direct la registrele Port D:

```cpp
void seteazaPiniInput(){
    DDRD &= ~((1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
    PORTD &= ~((1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
}

void activeazaRezistenta(int idx){
    seteazaPiniInput();
    DDRD |= (1 << indexRezistenteArray[idx]);
    PORTD |= (1 << indexRezistenteArray[idx]);
}
```

Avantaj: switching între rezistoare se face în câteva cicluri de clock, fără glitch-uri micro între pini.

### ADC manual prin registre

Înlocuim `analogRead()` cu acces direct la ADMUX și ADCSRA:

```cpp
// Configurare în setup()
ADMUX = (1 << REFS0);  // AVcc ca referință, canal A0
ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // enable + prescaler 128

// Citire
uint16_t citesteAdc(){
    ADCSRA |= (1 << ADSC);              // start conversion
    while (ADCSRA & (1 << ADSC));       // așteaptă terminare
    return ADC;
}
```

Beneficii pedagogice: înțelegere directă a fluxului ADC (configurare → start → wait → read). Performanță similară cu `analogRead()` la prescaler 128 (precizie maximă 10 biți reali).

### Detectie out-of-range în 2 puncte

1. **La discharge:** dacă ADC nu scade sub 10 LSB în 1 secundă (nu mai poate descărca = scurt-circuit sau condensator prea mare), returnează `false` și afișează "NO CAP / OOR".

2. **La averaging:** dacă mai puțin de 3 din 5 măsurători reușesc (restul timeout-uri), afișează "Out of range".

3. **La R = 1.1 MΩ după calibrare:** dacă capacitatea rezultată e sub 3 pF (după scăderea C_PARAZIT), afișează "No cap / < 3pF".

## Calcule și range util (Faza B)

### Range util per rezistor

| Rezistor | C_min util | C_max util | Comentariu |
|----------|------------|------------|------------|
| R1 = 1 kΩ | 200 nF | 1 mF | Pentru electrolitice mari |
| R2 = 10 kΩ | 20 nF | 100 µF | Range mediu-superior |
| R3 = 100 kΩ | 2 nF | 10 µF | Range mediu |
| R4 = 1.1 MΩ | 200 pF (după calibrare) | 100 nF | Range inferior, sensibil |

**Range total: ~180 pF - ~1 mF** (factor de 10 milioane).

### Timeout adaptiv per rezistor

- R = 1 kΩ → timeout **1.5 s** (acoperă până la ~1.5 mF teoretic)
- R = 10 / 100 kΩ / 1.1 MΩ → timeout **200 ms**

## Măsurători reale (Faza B)

| Cx nominal | Cx măsurat |  R ales |
|------------|------------|---------|
|   0.47uF   |  496.46nF  |    10k  |  
|   470uF    |  466uF     |    1k   |  
|   33uF     |  34.90     |     1k  |
|   68nF     |   82nF     |    100k |
|   1nF      |    1.01nF  |    1M   |


## Limitări observate (Faza B)

### 1. Capacități foarte mici (sub ~20 pF)

Calibrarea elimină capacitatea parazită constantă (205.735 pF), dar **zgomotul ADC + drift termic** introduc incertitudine de ±1-2 pF pentru orice măsurătoare. Pragul de 3 pF e limita sub care nu se poate distinge condensator de zgomot.

În plus, capacitățile parazite ale firelor/breadboard-ului variază cu temperatura (~50-200 ppm/°C). Calibrarea efectuată la o temperatură ambient drift-ează cu ~1-2 pF per câteva grade Celsius schimbare.

### 2. Electrolitice mari (sub R = 1 kΩ)

Pentru condensatori 470 µF - 1 mF, măsurătoarea durează 0.5-1 secundă. Plus discharge separat. Plus 5 măsurători pentru averaging. Total per afișaj: ~5-10 secunde. Utilizatorul așteaptă.

### 3. ESR la electrolitice vechi

Pentru electrolitice cu vârsta mare sau de calitate slabă, ESR (Equivalent Series Resistance) poate ajunge la 1-10 Ω. La R = 1 kΩ, asta introduce 0.1-1% eroare. Capacimetrul nu poate distinge între capacitate reală și capacitate aparentă cu ESR. Pentru cele mai multe electrolitice noi (ESR <100 mΩ), eroarea e neglijabilă.

### 4. Variație R cu temperatura

Rezistoarele E12 din stoc sunt de tip carbon film cu coeficient termic ~200-400 ppm/°C. Pe range mare de temperatură, asta introduce eroare. La temperatură stabilă camera, neglijabil.

## Ce am învățat (în plus față de Faza A)

- **Port manipulation directă** pe AVR (DDRD / PORTD / PIND) și operațiile pe biți (SET / CLEAR / TOGGLE / TEST cu masks)
- **Operatori pe biți în detaliu**: `|=`, `&= ~`, `^=`, `<<`, `~` și diferența între `=` și `|=` (capcana atribuirii directe)
- **Configurare ADC manuală prin registre**: ADMUX, ADCSRA, ADSC, prescaler, referință
- **Diferența între rezoluție și precizie ADC**: 10 biți teoretici vs ~9.5 biți ENOB efectivi
- **Concept de leakage current** la pini configurați INPUT (diode ESD, ~50 nA tipic, până la 1 µA worst case)
- **Loading effect** prin divizor cu impedanța de intrare ADC (~100 MΩ) și calcul corecție
- **Calibrare empirică** prin acumulare de măsurători (averaging cu N măsurători reduce zgomotul cu √N)
- **Concept de capacitate parazită** în sistem (breadboard, fire, pini)
- **Single source of truth** pentru cod (helper `seteazaPiniInput()` ca să nu duplici)
- **Tipuri întregi specificați** (uint16_t, unsigned long) și de ce sunt mai buni decât int generic
- **`static` în funcții** pentru variabile persistente între iterații
- **Tradeoff complexitate vs viteză**: averaging 5 vs 100 măsurători

## Cod

Fișierul complet: [main.cpp](./main.cpp)

Fragmentele cheie:

### Probing pentru selecție automată R

```cpp
int probing(){
    seteazaPiniInput();
    int idxR = 2;  // start cu R3 = 100 kΩ
    
    for(int i = 0; i < 3; i++){
        descarcareCondesator();
        activeazaRezistenta(idxR);
        delay(5);  // așteaptă fix 5 ms
        uint16_t v = citesteAdc();
        seteazaPiniInput();
        
        if(v >= 100 && v <= 920) return idxR;  // R bun
        
        if(v > 920){
            if(idxR == 3) return 3;  // saturare sus
            idxR++;
        } else {
            if(idxR == 0) return 0;  // saturare jos
            idxR--;
        }
    }
    return idxR;
}
```

### Măsurătoare finală cu averaging

```cpp
unsigned long sumaIncarcare = 0;
int cnt = 0;
for(int i = 0; i < 5; i++){
    tau = incarcare(indexRezistenta);
    if(tau != 0) {
        sumaIncarcare += tau;
        cnt++;
    }
    descarcareCondesator();
}
if(cnt < 3) {
    // out of range
} else {
    tau = sumaIncarcare / cnt;
}
```

### Calibrare și corecție pentru R = 1.1 MΩ

```cpp
if(indexRezistenta == 3) {
    capacitate /= 1.011;          // loading effect correction
    capacitate -= C_PARAZIT;       // scădere capacitate parazită
    if(capacitate < 3e-12) {
        afișează "No cap / < 3pF";
    }
}
```

## Roadmap evoluție (actualizat după Faza B)

### Faza A (completat) - Versiune minimă
- 1 rezistor referință, range 10 nF - 300 µF
- Cod simplu cu pinMode/digitalWrite/analogRead

### Faza B (completat) - Auto-range (curent)
- 4 rezistoare cu auto-range automat
- Port manipulation + ADC manual
- Calibrare capacitate parazită
- Range extins 180 pF - 1 mF
- Averaging pentru precizie statistică

### Faza C - Îmbunătățiri viitoare (planificate distribuit pe mai multe proiecte)
- Auto-range hardware cu MOSFET-uri 2N7000 (izolare mai bună, leakage mai mic)
- Detecție polaritate electrolitice
- Comparare cu valori standard E12 / E24
- Buton trigger manual (vs măsurători automate continue)
- Stocare ultimele 10 măsurători în EEPROM
- Auto-calibrare la pornire (vs C_PARAZIT hardcoded)
- Single-shot măsurare cu ln() pentru capacități la marginea range-ului
- Prescaler ADC adaptiv (rapid la probing, lent la măsurătoarea finală)
