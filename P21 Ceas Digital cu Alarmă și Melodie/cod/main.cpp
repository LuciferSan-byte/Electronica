#include <Arduino.h>
#include <EEPROM.h>
#include "melodie.h"

#define btnOra A0
#define btnMinute A1
#define buzzer 13
#define btnMod A3
#define btnOpritAlarma A4



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


bool modAlarma = false, alarmaActiva = false;
unsigned int oraAlarma = 0, minuteAlarma = 0;
unsigned long previousBtnMod = 0, previousBtnAlaram;


unsigned long previousSec = 0;
unsigned long previousMux = 0;
unsigned int cifraActiva = 0;
unsigned int pozActiv = 1;



unsigned int ora,minute,secunde;
int cifreCeas[4] = {1,2,3,4};

void setup() {
    Serial.begin(9600);
    for (int i = 2; i <= 12; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
  pinMode(buzzer, OUTPUT);
  pinMode(btnMinute, INPUT);
  pinMode(btnOra, INPUT);
  pinMode(btnMod, INPUT);
  pinMode(btnOpritAlarma, INPUT);
  digitalWrite(buzzer, LOW);

  ora = EEPROM.read(0);
  minute = EEPROM.read(1);
  oraAlarma = EEPROM.read(2);
  minuteAlarma = EEPROM.read(3);

  if(oraAlarma >= 24) oraAlarma = 0;
  if(minuteAlarma >= 60) minuteAlarma = 0;

  alarmaActiva = false;
  modAlarma = false;

  if (ora >= 24) ora = 0;
  if (minute >= 60) minute = 0;
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

void incrementeazaOra(){
    if(ora + 1 >= 24){
      ora = 0;
    }else ora++;

}
void incrementeazaMinute(){
  if(minute + 1 >= 60){
    minute = 0;
    incrementeazaOra();
  }else minute++; 
}
void incrementeazaSecunde(){
  if(secunde + 1 >= 60){
      secunde = 0;
      incrementeazaMinute();
  }else secunde++;
} 
void incrementeazaOraAlarma(){
    if(oraAlarma + 1 >= 24)
      oraAlarma = 0;
    else oraAlarma++;
}
void incrementeazaMinuteAlarma(){
    if(minuteAlarma + 1 >= 60)
      minuteAlarma = 0;
    else minuteAlarma++;
}

unsigned long previousBtnOra = 0;
unsigned long previousBtnMinute = 0;
void loop() {
    if (millis() - previousSec >= 1000) {
    previousSec = millis();
    incrementeazaSecunde();
    if (secunde == 0) {
        EEPROM.update(0, ora);
        EEPROM.update(1, minute);
    }
    }
    
    if (digitalRead(btnOpritAlarma) == HIGH && millis() - previousBtnAlaram >= 200){
      previousBtnAlaram = millis();
      alarmaActiva = false;
      opresteMelodie(buzzer);
    }

    if(digitalRead(btnMod) == HIGH && millis() - previousBtnMod >= 200){
      previousBtnMod = millis();
      modAlarma = !modAlarma;
      if(!modAlarma) alarmaActiva = true;
    }

    if (digitalRead(btnOra) == HIGH && millis() - previousBtnOra >= 200) {
       previousBtnOra = millis();
        if(!modAlarma){
          incrementeazaOra();
          EEPROM.update(0, ora);
          EEPROM.update(1, minute);
        }else{
          incrementeazaOraAlarma();
          EEPROM.update(2,oraAlarma);
          EEPROM.update(3,minuteAlarma);
        }
    }

    if (digitalRead(btnMinute) == HIGH && millis() - previousBtnMinute >= 200) {
        previousBtnMinute = millis();
        if(!modAlarma){
          incrementeazaMinute();
          EEPROM.update(0, ora);
          EEPROM.update(1, minute);
        }else{
          incrementeazaMinuteAlarma();
          EEPROM.update(2,oraAlarma);
          EEPROM.update(3,minuteAlarma);
        }
    }

  if (alarmaActiva && !modAlarma && ora == oraAlarma && minute == minuteAlarma && secunde == 0) {
    pornesteMelodie();
  }

    if(!modAlarma){
      cifreCeas[0] = ora / 10;
      cifreCeas[1] = ora % 10;
      cifreCeas[2] = minute / 10;
      cifreCeas[3] = minute % 10;
    }else{
      cifreCeas[0] = oraAlarma / 10;
      cifreCeas[1] = oraAlarma % 10;
      cifreCeas[2] = minuteAlarma / 10;
      cifreCeas[3] = minuteAlarma % 10;
    }
    redaMelodie(buzzer);
    if (millis() - previousMux >= 3) {
        previousMux = millis();
        for (int i = 2; i <= 8; i++) digitalWrite(i, LOW);
        activeazaPozitia(pozActiv);
        afiseazaCifra(cifreCeas[pozActiv - 1]);
        pozActiv++;
        if (pozActiv > 4) pozActiv = 1;
    }

}

