#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

extern const int backlightPin;

extern const int ledPin;
extern int ledState;
extern int prevLedState;

extern const int buzzerPin;
extern const int buttonPin;

extern int buttonState;

extern unsigned long startTime;
extern unsigned long stopTime;
extern unsigned long breakDuration;

extern String currentLetter;

extern bool isPressed;
extern bool printed;
extern int hasStart;

extern int digit;
extern int row;

extern int startCol;
extern int startRow;
extern bool hasLetterStart;
extern int symbolCount;
