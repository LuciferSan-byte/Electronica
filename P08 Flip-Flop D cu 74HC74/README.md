# P08 Flip-Flop D cu 74HC74

## Descriere
Flip-Flop D implementat cu 74HC74.
LED controlat de starea Q — se schimbă doar la frontul pozitiv al clockului.
Demonstrează conceptul de memorie digitală.

## Componente folosite
- 74HC74 Flip-Flop D
- Buton (clock manual)
- Switch DIP (intrare D)
- LED albastru
- Rezistor 330Ω (protecție LED)
- Alimentare 5V (de la Arduino)

## Tabel de adevăr
| CLK | D | Q (după clock) |
|-----|---|----------------|
| ↑ | 0 | 0 |
| ↑ | 1 | 1 |
| 0/1 | X | Q neschimbat |

## Conexiuni
- PIN 14 (VCC) → 5V
- PIN 7 (GND) → GND
- PIN 2 (D) → Switch DIP
- PIN 3 (CLK) → Buton cu pull-down
- PIN 4 (PRE) → 5V
- PIN 1 (CLR) → 5V
- PIN 5 (Q) → 330Ω → LED → GND

## Cum funcționează
FF-D memorează starea intrării D la frontul pozitiv al clockului.
Între clockuri — Q rămâne neschimbat indiferent de D.

D=HIGH → apăsare buton → Q=HIGH → LED aprins 
D=LOW → apăsare buton → Q=LOW → LED stins 
Fără apăsare → Q rămâne — memorie! 

## Lecții importante
- PRE și CLR floating → stare aleatorie la pornire!
  → soluție: PRE și CLR conectați la VCC
- 74HC74 la 9V → comportament ciudat
  → soluție: alimentare 5V obligatoriu
- Edge triggered — comută DOAR pe frontul pozitiv

## Ce am învățat
- FF-D — memorie 1 bit
- Edge triggered vs level triggered
- PRE și CLR — reset asincron
- Baza numărătoarelor binare
