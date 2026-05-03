# P07 Full Adder + Half Adder din RTL (BC547)

## Descriere
Implementare hardware completă a unui Half Adder și Full Adder
folosind exclusiv tranzistoare BC547 în logică RTL.
Toate porțile logice construite din NAND-uri RTL discrete.

## Componente folosite
- BC547 NPN — multe tranzistoare (~20+)
- Rezistoare colector și bază
- LED-uri pentru Sum și Carry
- Switch-uri DIP pentru intrări
- Breadboard x2
- Alimentare 5V

## Arhitectura RTL
Toate porțile construite din NAND-uri RTL (BC547):
- **XOR** = 4 porți NAND
- **AND** = NAND + invertor
- **OR** = NAND cu intrări negate

## Half Adder
**Sum = A XOR B**
**Carry = A AND B**

| A | B | Sum | Carry |
|---|---|-----|-------|
| 0 | 0 | 0 | 0 |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 1 | 0 |
| 1 | 1 | 0 | 1 |

## Full Adder
**Sum = A XOR B XOR Cin**
**Cout = (A AND B) OR (Cin AND (A XOR B))**

Implementat ca: 2x Half Adder + poartă OR

| A | B | Cin | Sum | Cout |
|---|---|-----|-----|------|
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 | 0 |
| 0 | 1 | 0 | 1 | 0 |
| 0 | 1 | 1 | 0 | 1 |
| 1 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |

## Cum funcționează
Half Adder 1: calculează Sum1 = A XOR B și Carry1 = A AND B
Half Adder 2: calculează Sum = Sum1 XOR Cin și Carry2 = Sum1 AND Cin
OR final: Cout = Carry1 OR Carry2

## Ce am învățat
- Universalitatea NAND — orice poartă din NAND-uri
- XOR din 4 NAND-uri
- Full Adder = 2x Half Adder + OR
- RTL — Resistor Transistor Logic
- Logica binară implementată în hardware
