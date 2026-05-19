#include <Arduino.h>

const int voltmetru = A0;

const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;

const int dig1 = 9;
const int dig2 = 10;
const int dig3 = 11;
const int dig4 = 12;

const int dot  = 13;

unsigned long previousMux = 0;
unsigned long previousVolt = 0;

unsigned int  pozActiv    = 1;

const float vRef = 4.60; // tensiunea de la arduino

int cifreVolt[4]{};
int intregRaw, zecimalRaw;
int valoareaRaw;
float tensiuneReala;

void setup() {
    
    for (int i = 2; i <= 13; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
}
void activeazaPozitia(int pozitie){
  for (int i = 9; i <= 12; i++) {
        digitalWrite(i, LOW);
    }
    switch(pozitie){
      case 1: 
      digitalWrite(dig1, HIGH);
        break;
      case 2: 
      digitalWrite(dig2, HIGH);
        break;
      case 3: 
      digitalWrite(dig3, HIGH);
        break;
      case 4: 
      digitalWrite(dig4, HIGH);
        break;
    } 
}
void afiseazaCifra(int cifra){
   for (int i = 2; i <= 8; i++) {
        digitalWrite(i, LOW);
    }
    switch(cifra){
      case 0: 
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        break;
      case 1:
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        break;
      case 2:
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segG, HIGH);
        break;
      case 3:
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segG, HIGH);
        break;
      case 4:
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;
      case 5:
        digitalWrite(segA, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segG, HIGH);
        digitalWrite(segF, HIGH);
        break;
      case 6:
        digitalWrite(segA, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;
      case 7:
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        break;
      case 8:
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;
      case 9:
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;
      default:
        for (int i = 2; i <= 8; i++) {
        digitalWrite(i, LOW);
      } 
      break;
    }
}
void loop() {
  if(millis() - previousVolt >= 100){
    previousVolt = millis();
    
    long suma = 0;
    for(int i = 0; i < 50; i++){
      suma += analogRead(voltmetru);
    }
    
    valoareaRaw = suma / 50;
    
    float tensiuneNoua = (valoareaRaw * 6.0 * vRef) / 1024.0;
    static float ultimaValoare = 0;
    if( abs(tensiuneNoua- ultimaValoare) > 0.05){
      ultimaValoare = tensiuneNoua;
      tensiuneReala = tensiuneNoua;
    
    intregRaw = (int)tensiuneReala;
    zecimalRaw = (int)(tensiuneReala * 100) % 100;
    
    cifreVolt[0] = intregRaw / 10;
    cifreVolt[1] = intregRaw % 10;
    cifreVolt[2] = zecimalRaw / 10;
    cifreVolt[3] = zecimalRaw % 10;
    }
  }
  if (millis() - previousMux >= 2) {
        previousMux = millis();
        for (int i = 2; i <= 8; i++)
           digitalWrite(i, LOW);
        digitalWrite(dot, LOW);
        
        if(pozActiv == 1 && cifreVolt[0] == 0 ){
          digitalWrite(dig1, LOW);
          pozActiv++;
        }
        activeazaPozitia(pozActiv);
        afiseazaCifra(cifreVolt[pozActiv - 1]);
        if(pozActiv == 2) 
          digitalWrite(dot, HIGH);
        
        pozActiv++;
        if (pozActiv > 4) pozActiv = 1;
    }
}
