#include <Arduino.h>

#define LED_PIN 2
#define TRIG 13
#define ECHO 12
#define PRAG 20

const float SOUND_SPEED = 0.0343; // cm/us

long duration;
int cm;

void setup() {
  Serial.begin(9600);
  delay(3000);

  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  if (duration == 0) {
    Serial.println("Eroare: niciun semnal");
    return;
  }

  cm = (duration * SOUND_SPEED) / 2;

  Serial.print(cm);
  Serial.println(" cm");

  if (cm < PRAG) {
    Serial.println("Obiect detectat!");
  }

  digitalWrite(LED_PIN, cm < PRAG ? HIGH : LOW);

  delay(250);
}
