# P06 — Poartă XOR cu 74HC86

## Descriere
Implementare hardware a porții logice XOR folosind 74HC86.
LED aprins doar când intrările sunt diferite — "sau exclusiv".

## Componente folosite
- 74HC86 (XOR quad 2-input)
- Rezistoare pull-down 10kΩ x2 (pe intrări)
- Rezistor 470Ω (protecție LED)
- LED albastru
- 2x butoane/switch-uri
- Alimentare 5V

## Tabel de adevăr XOR
| A | B | Output |
|---|---|--------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

## Conexiuni
- VCC → Pin 14
- GND → Pin 7
- Switch A → Pin 1 + pull-down 10kΩ → GND
- Switch B → Pin 2 + pull-down 10kΩ → GND
- Pin 3 (Output) → 470Ω → LED → GND

## Verificare hardware
Toate 4 combinații testate și confirmate 

## Cum funcționează
XOR = "sau exclusiv" — output HIGH doar când intrările sunt DIFERITE.
Ori A=1 ori B=1 — nu amândouă și nu niciuna.
Pull-down asigură stare definită când switch-ul e deschis.

## Ce am învățat
- Poarta XOR și tabelul de adevăr
- 74HC86 — alimentare MAX 6V → folosim 5V
- Pull-down pe intrări — pin nu floating
- XOR folosit în: detectare diferențe, Gray code, sumatoare
