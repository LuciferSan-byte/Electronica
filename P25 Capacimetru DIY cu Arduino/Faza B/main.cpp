
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <avr/io.h>

#define THRESHOLD_ADC 647

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; // oini ecran lcd

// rezistentele prin care se incaraca condesatoru
// R1 = 974 ohm       pin 4
// R2 = 9.840 ohm     pin 5
// R3 = 99.100 ohm    pin 6
// R4 = 1.000.000 ohm pin 7

const float C_PARAZIT = 205.735e-12;

const float rezistente[4] = {974.0,9840.0,99100.0,1000000.0};

const int indexRezistenteArray[4] = {PD4,PD5,PD6,PD7}; // pini incarcare condesator
const char* rFolosite[4] = {"1k","10k","100k","1.1M"};
const unsigned long timeoutPentruR[4] = {1500000, 200000, 200000, 200000}; // R1 = 1.5s, {R2,R3,R4} = 200ms timeout

// pinul de descarcare a condesatorului este PD3 si se descarca printr - o rezistenta de 220 ohm pentru a limita curentu prin arudiono la ~22mA

const int masurare = A0; // pinul pentru masurarea tensiunii la bornele condesatorulului


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  ADMUX = (1 << REFS0); // rescrie tot registrul: REFS0 = 1 (spune adc ul sa foloseasca ca referinta avcc);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //da enable la adc si seteaza prescalerul la 128 
  
  lcd.begin(16, 2);

}

void lcdClear(){
  lcd.clear();
  lcd.setCursor(0,0);
}

void seteazaPiniInput(){
  DDRD &= ~((1 << PD3) |(1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7)); // seteaza pinii in modul input default
  PORTD &= ~((1 << PD3) |(1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7)); // seteaza pini in modul hi-z dezactiveaza rezistenta interna de pull up
}

void activeazaRezistenta(int indexRezistenta){

  if(indexRezistenta < 0 || indexRezistenta > 3){
    Serial.print("Eroare: index invalid");
    indexRezistenta = abs(indexRezistenta) % 4;
  }

  seteazaPiniInput();

  DDRD |= (1 << indexRezistenteArray[indexRezistenta]);
  PORTD |= (1 << indexRezistenteArray[indexRezistenta]);
}


uint16_t citesteAdc(){
  ADCSRA |= (1 << ADSC); // porneste masuratoarea

  while (ADCSRA & (1 << ADSC)); // astepta pana cand masuratoarea e finalizata

  return ADC;
}


bool descarcareCondesator(){
  seteazaPiniInput();

  DDRD |= (1 << PD3);
  PORTD &= ~((1 << PD3));

  unsigned long timerDescarcare = millis();

  while(citesteAdc() > 10 && (millis() - timerDescarcare) < 1000);
  DDRD &= ~((1 << PD3));

  return ((millis() - timerDescarcare) < 1000);
}

unsigned long incarcare(int idxR){
  seteazaPiniInput();

  unsigned long timerIncarcare;

  activeazaRezistenta(idxR);
  timerIncarcare = micros();

  while(THRESHOLD_ADC > citesteAdc() && ((micros() - timerIncarcare) < timeoutPentruR[idxR]));
  
  unsigned long tau = micros() - timerIncarcare;

  seteazaPiniInput();

  if(tau < timeoutPentruR[idxR]) return tau;
  return 0;

}

int probing(){
  seteazaPiniInput();
  int idxR = 2; // Rezistenta de 100k 

  for(int i = 0; i < 3; i++){
    
    descarcareCondesator(); // seteaza automat pinii la modul input dupa finalizarea descarcarii 

    activeazaRezistenta(idxR);
    delay(5);
    uint16_t v = citesteAdc();

    seteazaPiniInput(); 


    if(v >= 100 && v <= 920) return idxR;

    if(v > 920){
      if(idxR == 3) return 3;
      idxR++;
    } else {

      if(idxR == 0) return 0;
      idxR--;
    }
  }

  descarcareCondesator(); // descarca condesatorul si seteaza pinii la modul input
  return idxR;
}

float formula(float secunde, float rezistor){
  return secunde / (float)rezistor;
}

void valoareF(float capacitate, int index){
  lcdClear();


  if(capacitate * 1e6 >= 1){
    lcd.print(capacitate * 1e6,2);
    lcd.print(" uF");

  }else if(capacitate * 1e9 >= 1){
    lcd.print(capacitate * 1e9,2);
    lcd.print(" nF");

  }else if(capacitate * 1e12 >= 1){
    lcd.print(capacitate * 1e12,1);
    lcd.print(" pF");
  }
  lcd.setCursor(0,1);
  lcd.print("R: ");
  lcd.print(rFolosite[index]);
}


void loop() {
  
  unsigned long tau;

  lcdClear();
  if(!descarcareCondesator()){
    lcdClear();
    lcd.print("NO CAP / OOR");
    delay(2000);
    return;
  }

  int indexRezistenta = probing();
  descarcareCondesator();
  
  unsigned long sumaIncarcare = 0;
  int cnt = 0;
  for(int i = 0; i < 5 ; i++){

    tau = incarcare(indexRezistenta);
    if(tau != 0) {
      sumaIncarcare += tau;
      cnt ++;
    }

    descarcareCondesator();
  }

  if(cnt < 3) {
    lcdClear();
    lcd.print("Out of range");
    delay(2000);
    return;
  }else{
    tau = sumaIncarcare / cnt;
  }

  float secundeTau = (float)tau * 1e-6;

  float capacitate = formula(secundeTau, rezistente[indexRezistenta]);
  if(indexRezistenta == 3) {
    capacitate /= 1.011; // corectia pentru loading effect
    capacitate -= C_PARAZIT;
    if(capacitate < 3e-12)  {
      lcdClear();
      lcd.print("No cap / < 3pF");
      lcd.setCursor(0, 1);
      delay(2000);
      return;
    }
  }
  valoareF(capacitate,indexRezistenta);

  delay(3000);
  
}
