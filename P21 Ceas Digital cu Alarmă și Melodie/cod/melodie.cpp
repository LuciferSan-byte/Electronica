#include "melodie.h"
#include <Arduino.h>

int tempo = 122;

int melody[] = {
    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8,
    NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
    NOTE_A4, 4, NOTE_C4, 8, NOTE_C4, 4, NOTE_C4, 8, NOTE_C4, 4,
    NOTE_C4, 1,

    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8,
    NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
    NOTE_A4, 4, NOTE_C4, 8, NOTE_C4, 4, NOTE_C4, 8, NOTE_C4, 4,
    NOTE_C4, -2,  REST, -8, NOTE_A4, 16,

    NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
    NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16,
    NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
    NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16,

    NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
    NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16,
    NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
    NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16,

    NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8,
    NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
    NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_A4, 4,
    NOTE_G4, 1,
    NOTE_C5, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_A4, 4, NOTE_C5, 8,
    NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
    NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_A4, 4,
    NOTE_G4, 1,

    NOTE_C5, 1,
    NOTE_C5, 4, NOTE_AS4, 8, NOTE_C5, 8, NOTE_AS4, 2,
    NOTE_A4, 4, NOTE_C4, 8, NOTE_C4, 4, NOTE_C4, 8, NOTE_C4, 4,
    NOTE_C4, 1,

    REST, 4, NOTE_A4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, 8, NOTE_C4, 8,
    NOTE_D4, 1,
    REST, 4, NOTE_A4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, 8, NOTE_C4, 8,
    NOTE_D4, 1
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;

int notaCurenta = 0;
unsigned long previousNota = 0;
unsigned long durataNota = 0;
bool melodieActiva = false;

void pornesteMelodie(){
    melodieActiva = true;
    notaCurenta = 0;
}
void opresteMelodie(int buzzerPin){
    melodieActiva = false;
    notaCurenta = 0;
    noTone(buzzerPin);
    digitalWrite(buzzerPin, LOW); 
}

void redaMelodie(int buzzerPin) {
    if(!melodieActiva) return;

    if(millis() - previousNota >= durataNota){
        previousNota = millis();

        if(notaCurenta >= notes*2){
            notaCurenta = 0;
            return;
        }

        int divier = melody[notaCurenta + 1];
        if(divier > 0){
            durataNota = wholenote / divier;
        }else{
            durataNota = (wholenote/abs(divier)) * 1.5;
        }
        
        tone(buzzerPin, melody[notaCurenta], durataNota * 0.9);

        notaCurenta += 2;

    }
}