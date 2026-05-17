# P23 Multiplicator de tensiune Cockcroft-Walton (9 etaje)

## Descriere proiect

Multiplicator de tensiune Cockcroft-Walton cu 9 etaje. Circuitul funcționează prin pomparea alternată a sarcinii electrice de la un condensator la altul. În locul unui semnal sinusoidal pur, am folosit un NE555 astabil pentru a produce un semnal PWM de 10 kHz simulând un semnal alternativ.

## Componente folosite

- 1 × NE555 (oscilator astabil 10 kHz)
- 9 × Diode 1N4007
- 9 × Condensatoare electrolitice 0.22µF / 50V
- Rezistoare pentru NE555: 1 × 1kΩ, 1 × 6.8kΩ
- Condensator timing NE555: 1 × 10nF
- Condensator decuplare NE555: 1 × 100nF
- 2 × breadboard
- Fire solid-core

## Arhitectura circuitului

### Etaj 1 — Oscilator NE555 astabil

NE555 astabil folosit pentru a produce un semnal PWM de 10 kHz, simulând semnalul de curent alternativ necesar multiplicatorului.

- R1 = 1kΩ, R2 = 6.8kΩ, C = 10nF
- Frecvență calculată: 9.86 kHz
- Duty cycle: 53.4%

### Etaj 2 — Lanțul Cockcroft-Walton (9 etaje)

În primul semi-ciclu, semnalul oscilator încarcă primul condensator ca pe o baterie normală. În următorul semi-ciclu, când semnalul își schimbă sensul, tensiunea stocată se adună cu tensiunea sursei, dublând tensiunea care încarcă următorul condensator din lanț. Procesul se repetă pe lanțul de etaje, acumulând tensiunea progresiv.

## Calcule

### Tensiunea de output teoretică

Vin_peak NE555 ≈ 3.3V (din datasheet, V_OH la Vcc = 5V)

| Multiplicator | Vout Ideal | Pierderi diode | Vout Real teoretic |
|---------------|------------|----------------|---------------------|
| x9 | 9 × 3.3 = 29.7V | 9 × 0.7 = 6.3V | 23.4V |

### Dimensionare condensator

Pentru 10 kHz, perioada T = 100µs.
Constanta de timp τ = R_serie × C, unde R_serie ≈ 100Ω (rezistența surse + diodă).

Cu C = 0.22µF (220nF): τ ≈ 22µs, ceea ce permite încărcare aproape completă într-o jumătate de perioadă (50µs).

### Rezultate simulare

| Etaj | Vout simulat |
|------|--------------|
| 1 | ~4V    |
| 2 | ~8V    |
| 3 | ~11.4V |
| 4 | ~15.4V |
| 5 | ~19V   |
| 6 | ~22.6V |
| 7 | ~26V   |
| 8 | ~30V   |
| 9 | ~33V   |

## Măsurători reale pe breadboard

| Locație | Vout măsurat |
|---------|--------------|
| Output final (etaj 9) | 30V |

În simulare, output-ul ultimului etaj este 33V, iar măsurătorile reale pe breadboard arată 30V. Diferența de ~3V vine din pierderile reale (Vf-ul diodei la curent mic în practică, ESR-ul condensatoarelor electrolitice, rezistența firelor și a contactelor pe breadboard).

## Probleme întâlnite

- Am încercat să fac un subcircuit în LTspice pentru un etaj cascadabil, dar nu a funcționat (probabil din cauza faptului că topologia Cockcroft-Walton e integrată, nu modulară per etaj). Am revenit la schema flat — a funcționat.
- Atenție la polaritatea condensatoarelor electrolitice — orientarea greșită ar produce defectarea.

## Ce am învățat

- Charge pump (mecanism fundamental)
- Cascadarea Cockcroft-Walton
- Pierderi pe diode care se acumulează în multiplicatoare
- Tranzitoriu vs steady-state
- Ripple progresiv pe etaje superioare
- Diferența între topologie modulară și topologie integrată în SPICE
- Polaritate condensatori electrolitici (atenție la orientare)
- Siguranță pentru tensiuni peste 20V (descărcare condensatori după utilizare)

## Limitări observate

- Eficiența scade cu numărul de etaje (din cauza pierderilor pe diode)
- Curent disponibil la output e foarte mic (multimetrul ca singura sarcină)
- Dioda Schottky ar îmbunătăți performanța circuitului — are cădere de tensiune mult mai mică (~0.2V vs ~0.7V pentru 1N4007)

## Foto

![Grafic simulare](./poze/grafic_spice.jpeg)
![Breadboard complet](./poze/breadboard.jpeg)

---

**Notă siguranță:** Multiplicatoarele de tensiune au condensatoare care rămân încărcate după decuplarea alimentării. Pentru manipulare în siguranță, descărcați condensatoarele cu un rezistor (1-10kΩ) între output și GND timp de cel puțin 30 secunde înainte de a atinge circuitul.
