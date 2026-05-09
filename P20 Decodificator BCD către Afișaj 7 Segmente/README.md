# P20 Decodificator BCD către Afișaj 7 Segmente

## Componente folosite
- Display 7 segmente common anode (1 cifră)
- 7x BC547 NPN (drivere segmente)
- Chip-uri logice: 74HC08 (AND), 74HC32 (OR), 
  74HC02 (NOR), 74HC86 (XOR), 74LS00 (NAND)
- Rezistoare: 330Ω x7 (segment), 10kΩ x11 (bază + pull-down)
- 4x butoane + 4x rezistoare pull-down 10kΩ
- Alimentare: 5V

## Calcule
- Câștig segment: Rc = (Vcc - Vce - Vf) / If = (5 - 0.2 - 3.5) / 0.015 = 286Ω → 330Ω
- Rb BC547 = 10kΩ → Ib = 0.43mA >> Ib_necesar = 0.07mA 
- Expresii logice din K-map (4 variabile):
  - A_seg = B̄·D̄ + C + B·D + A
  - B_seg = B̄ + C̄·D̄ + C·D
  - C_seg = C̄ + D + B
  - D_seg = B̄·D̄ + B·C + B·C̄·D + C·D̄
  - E_seg = B̄·D̄ + C̄·D̄
  - F_seg = C̄·D + B̄·C + B·D + A
  - G_seg = B̄·C + B·C̄ + A + C·D̄

## Măsurători reale
- Toate cifrele 0-9 afișate corect 
- Tensiune ieșire chip logic HIGH: 5V 
- Tensiune ieșire chip logic LOW: 0V 
- Luminozitate uniformă pentru toate cifrele 
- Cifre invalide 10-15: output don't care (comportament corect) 

## Probleme întâlnite
- Conexiuni greșite între porți față de schema din Logisim → depanat fir cu fir
- Mix 74LS/74HC evitat prin separarea logicii pe segmente
- Fire multe → organizare pe culori necesară pentru debugging

## Ce am învățat
- K-map pentru 4 variabile și minimizarea funcțiilor logice
- Don't care (X) în K-map permite grupuri mai mari → expresii mai simple
- BC547 ca driver între logică digitală și display
- Decoder discret = echivalentul manual al chip-ului CD4511
- Pull-down obligatoriu pe intrări pentru evitarea pinilor floating
- Separarea alimentării logicii (5V) de alimentarea display-ului
