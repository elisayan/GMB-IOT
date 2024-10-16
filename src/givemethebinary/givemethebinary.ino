/*
 * Assignment #1 - Give Me the Binary! (GMB)
 * Author: Elisa Yan
 */

#include <LiquidCrystal.h>
#include <avr/sleep.h>
#include "Game.h"

unsigned long lastButtonPressTime = 0;

const int ledPins[] = { 13, 12, 11, 10 };
const int buttonPins[] = { 2, 3, 4, 5 };
const int potPin = A0;
const int ledRedPin = A1;

const unsigned long sleepTimeout = 10000;


static bool gameStarted;

//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void wakeUp() {
}

void setup() {
  Serial.begin(9600);

  //lcd.begin(16, 2);
  //lcd.print("Welcome to GMB!");
  //lcd.setCursor(0, 1);
  //lcd.print("Press B1 to Start");

  Serial.println("Welcome to GMB! Press B1 to Start");

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
    digitalWrite(ledPins[i], LOW);
    attachInterrupt(digitalPinToInterrupt(buttonPins[i]), wakeUp, RISING);
  }
  pinMode(ledRedPin, OUTPUT);

  lastButtonPressTime = millis();
}

void loop() {
  int newValue = analogRead(potPin);

  gameStarted = false;

  if (!gameStarted) {

    if (millis() - lastButtonPressTime >= sleepTimeout) {
      Serial.println("going to sleep");
      Serial.flush();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      sleep_disable();
      Serial.println("wake up");
      lastButtonPressTime = millis();
    }
    pulseRedLED(ledRedPin);
    setDifficulty(ledRedPin, potPin);

    if (isAwake(buttonPins[0])) {
      gameStarted = true;
      //lcd.clear();
      //lcd.print("Go!");
      Serial.println("Go!");
      digitalWrite(ledRedPin, LOW);
      start(ledPins);
      Serial.println(newValue);
    }
  }
}
