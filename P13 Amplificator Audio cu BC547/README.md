# P13 — Amplificator Audio cu BC547

## Descriere
Amplificator clasa A cu BC547.
NE555 ~1kHz ca sursă de semnal.
Ieșire pe difuzor 8Ω prin condensator de cuplaj.

## Componente folosite
- BC547 NPN (amplificator)
- NE555 astabil ~1kHz (sursă semnal)
- R_C = 1kΩ (colector)
- R_E = 150Ω (emitor — stabilizare termică)
- R1 = 20kΩ + 10kΩ = 30kΩ (divizor bază)
- R2 = 5.6kΩ (divizor bază)
- C_cuplaj intrare = 1µF
- C_cuplaj ieșire = 1µF
- Difuzor 8Ω

## Calcule punct Q
**I_C ales = 5mA**
**V_CE = VCC/2 = 8.3/2 ≈ 4.15V** (punct Q la mijloc)

**R_C = V_CE / I_C = 4.15 / 0.005 = 830Ω → 1kΩ** 

**R_E = 10% × R_C = 100Ω → 150Ω** 

**V_RE = I_C × R_E = 0.005 × 150 = 0.75V**
**V_B = V_BE + V_RE = 0.7 + 0.75 = 1.45V**

**I_B = I_C / h_FE = 5mA / 200 = 0.025mA**
**I_div = 10 × I_B = 0.25mA**
**R_total = VCC / I_div = 8.3 / 0.00025 = 33.2kΩ**

**R2 = V_B / I_div = 1.45 / 0.00025 = 5800Ω → 5.6kΩ** 
**R1 = R_total - R2 = 33.2k - 5.6k = 27.6kΩ → 30kΩ** 

## Calcul condensatori cuplaj
**f_taiere = 1 / (2π × R2 × C)**
C = 1 / (2π × 5600 × 100) = 0.28µF → 1µF 

## Măsurători reale
| Parametru | Teoretic | Măsurat |
|-----------|----------|---------|
| V_B | 1.45V | 1.0V |
| V_E | 0.75V | 0.3V |
| V_C | 4.15V | 1.80V |
| V_CE | 4.15V | 1.50V |

Diferențe din cauza bateriei descărcate (8.3V în loc de 9V)

## Cum funcționează
Divizorul R1/R2 setează V_B fix → punct Q stabil.
Semnal AC de la NE555 intră prin C_cuplaj → nu perturbă DC.
BC547 în zonă activă amplifică semnalul.
C_cuplaj ieșire blochează DC → difuzorul primește doar AC.
R_E stabilizează termic punctul Q.

## Probleme întâlnite
- NE555 conectat direct la bază → perturbă punctul Q
  → soluție: condensator de cuplaj 1µF
- Baterie descărcată → V_CE mai mic decât teoretic

## Ce am învățat
- Punct de funcționare Q — amplificator clasa A
- Divizor de tensiune pentru stabilizare bază
- Condensator de cuplaj — blochează DC, lasă AC
- R_E — stabilizare termică
- Impedanță mare divizor vs I_B
