#include <Arduino.h>
#include <LiquidCrystal.h>


const int rs = 4, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13; // oini ecran lcd
const int charge = 8; // pinul prin care se va incarca condesatoru , prin rezistenta de 10k
const int disCharge = 9; // pinul prin care se descarca condesatoru, fara rezistenta
const int masurare = A0; // pinul pentru masurarea tensiunii la bornele condesatorulului

const int Rfix = 9890; //rezistenta prin care se incarca condesatoru

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  pinMode(disCharge, INPUT);
  pinMode(charge, INPUT);
  lcd.begin(16, 2);

}

void lcdClear(){
  lcd.clear();
  lcd.setCursor(0,0);
}

bool descarcare(){
  unsigned long timpD = millis();

    pinMode(charge,INPUT);
    pinMode(disCharge, OUTPUT);
    digitalWrite(disCharge, LOW);

    while(analogRead(masurare) > 50){
      if (millis() - timpD > 100) {
        return false;
      }

      delay(1);
    }
  return true;
}

unsigned long incarcare(){

  unsigned long timpIncarcare = micros();
    lcdClear();
    lcd.print("Charging...");
    pinMode(charge, OUTPUT);
    pinMode(disCharge, INPUT);
    digitalWrite(charge, HIGH);
    
    delayMicroseconds(50);  // așteaptă 50µs
    
    if (analogRead(masurare) > 900) {
        return 0;  // detectare "No Cap"
    }
    
    while (analogRead(masurare) < 647) {
        if (micros() - timpIncarcare > 3000000) {
            return 0;
        }
    }
    return micros() - timpIncarcare;

}

void idle(){
  pinMode(charge,INPUT);
  pinMode(disCharge, OUTPUT);
}

float formula(float secunde){
  return secunde / Rfix;
}

void valoareF(float capacitate){
  lcdClear();

  if(capacitate * 1e6 >= 1){
    lcd.print(capacitate * 1e6);
    lcd.print(" uF");
    return;
  }
  if(capacitate * 1e9 >= 1){
    lcd.print(capacitate * 1e9);
    lcd.print(" nF");
    return;
  }
  if(capacitate * 1e12 >= 1){
    lcd.print(capacitate * 1e12);
    lcd.print(" pF");
    return;
  }
  
}


void loop() {

  float capacitate;

  if(!descarcare()){
    idle();
    lcdClear();
    lcd.print("No Cap");
    delay(1000);
    return;
  }

  lcdClear();

  float timpMacros = incarcare();

  if(timpMacros == 0) {
    idle();
    lcdClear();
    lcd.print("No Cap / OOR");
    delay(2000);
    return;}

  float timpSecunde = timpMacros / 1000000.0;
  capacitate = formula(timpSecunde);


  valoareF(capacitate);
  delay(5000);
}
