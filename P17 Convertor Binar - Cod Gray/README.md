# P17 — Convertor Binar → Cod Gray cu TTL din BC547

## Descriere
Extensie a proiectului #9 — numărătorul binar 6 biți.
Conversia binar → Gray implementată cu porți logice TTL
construite manual din tranzistoare BC547.

## Ce este Codul Gray
Reprezentare binară unde doar 1 bit se schimbă la fiecare pas.
Util în encodere rotative, comunicații, prevenirea erorilor.

## Formula conversie Binar → Gray
- G3 = B3
- G2 = B3 XOR B2
- G1 = B2 XOR B1
- G0 = B1 XOR B0

## Componente folosite
- BC547 NPN — ~24 tranzistoare (porți NAND TTL + buffere)
- Rezistoare Rs = 1kΩ (bază), Rc = 1.8kΩ (colector)
- Rezistoare pull-down 10kΩ pe intrări
- LED albastru x4 (afișare Gray)
- LED albastru x4 (afișare Binar)
- Rezistoare 330Ω pentru LED-uri
- Butoane pentru input manual
- Breadboard x2

## Arhitectura circuitului
Fiecare XOR = 4 porți NAND TTL
Fiecare NAND TTL = 2 BC547 emitor multiplu simulat + 1 BC547 buffer

Schema NAND TTL:
- T1 și T2: baze împreună, emitoare = intrări A și B
- Colectoare T1+T2 → baza T3 (output stage)
- Buffer BC547 la ieșire pentru izolare impedanță

## Problema rezolvată
Fără buffer → degradare semnal la înlănțuire NAND→NAND
Cu buffer → impedanță mare intrare, mică ieșire → semnal curat 

## Măsurători
Testat toate combinațiile — output Gray corect 

## Probleme întâlnite
- TTL fără buffer → degradare semnal
  → soluție: buffer între fiecare poartă
- Intrări floating → comportament aleatoriu
  → soluție: pull-down 10kΩ
- Schema inițială greșită
  → soluție: emitoare = intrări, nu baze

## Ce am învățat
- TTL din tranzistoare — emitor multiplu simulat
- Buffer = impedanță mare intrare, mică ieșire
- XOR din 4 NAND-uri
- Conversia binar → Gray în hardware
- De ce buffer-ul e necesar între etaje logice
