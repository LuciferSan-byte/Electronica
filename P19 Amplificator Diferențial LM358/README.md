# P18` Amplificator Diferențial LM358
## Componente folosite
- LM358 Op-Amp
- R1=R2=1kΩ, R3=R4=10kΩ
- Baterie 9V
## Calcule
- Câștig = R3/R1 = 10k/1k = 10
- Vout = (V+ - V−) × 10
- Vout max = Vcc - 2V = 7V
- Diferență max sigură = 0.7V
## Măsurători reale
| V+ | V− | Vout calculat | Vout măsurat |
|----|----|---------------|--------------|
| 1.97 | 1.62 | 3.50V | 3.52V |
| 1.90 | 1.70 | 2.00V | 2.00V |
| 1.50 | 1.00 | 5.00V | 5.00V |
## Probleme întâlnite
- Toleranța rezistoarelor afectează CMRR
-Am calculat CMRR sa vad rezistenta circuitului la zgomot
- Mod comun nu e perfect 0V din cauza asimetriei
-Loading efect intalnit am marit rezistenta ca sa reduc loading effect ul
## Ce am învățat
- CMRR = 42.5 dB
- Loading effect la măsurători
- LM358 output swing = Vcc - 2V
