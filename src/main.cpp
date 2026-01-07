#include <Arduino.h>
#include <LiquidCrystal.h>

#include "app_config.h"
#include "app_state.h"
#include "lcd_ui.h"
#include "app_logic.h"
#include "morse_decoder.h"

void setup();
void loop();


/* ===================== LCD (16x2) ===================== */
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

const int backlightPin = LCD_BACKLIGHT_PIN;

// LED
const int ledPin = LED_PIN;
int ledState = LOW;
int prevLedState = LOW;

// Buzzer + Button
const int buzzerPin = BUZZER_PIN;
const int buttonPin = BUTTON_PIN;

// Button
int buttonState;

// Duration
unsigned long startTime = 0;
unsigned long stopTime = 0;
unsigned long breakDuration = 0;

// Current letter store
String currentLetter = "";

// print
bool isPressed = false;
bool printed = false;
int hasStart = 0;

// digit shifting
int digit = 0;
int row = 0;

int startCol = 0;
int startRow = 0;
bool hasLetterStart = false;
int symbolCount = 0;

void setup() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  analogWrite(backlightPin, LCD_BACKLIGHT_PWM);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  delay(10);

  lcd.clear();
  lcd.print("Morse Code");
}

void loop() {
  buttonState = digitalRead(buttonPin);
  ledState = digitalRead(ledPin);

  // Clear screen when start
  while (hasStart == 1) {
    delay(100);
    lcd.clear();
    hasStart++;
  }
  if (buttonState == LOW) {
    hasStart++;
  }

  // Print symbols
  if (buttonState == HIGH) {
    delay(10);
    checkState();
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  } else {
    delay(10);
    checkState();
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 800);
  }

  // Determine the time to print characters
  if (buttonState == LOW && isPressed) {
    isPressed = false;
  } else if (buttonState == HIGH && !isPressed) {
    isPressed = true;
    printed = false;
    breakDuration = millis();
  }

  if (buttonState == HIGH && isPressed && hasStart > 1) {
    unsigned long heldTime = millis() - breakDuration;
    if (heldTime >= 1000 && !printed) {
      delay(10);
      updateScreen();
      printed = true;
    }
  }
}