#include <Arduino.h>

#include "app_config.h"
#include "app_state.h"
#include "lcd_ui.h"
#include "app_logic.h"
#include "morse_decoder.h"

// Check led state & print symbol
void checkState() {
  if (ledState != prevLedState) {
    if (ledState == HIGH) {
      delay(10);
      startTime = millis();
    } else {
      delay(10);
      stopTime = millis();
      unsigned long duration = stopTime - startTime;

      lcd.setCursor(digit, row);

      if (!hasLetterStart) {
        startCol = digit;
        startRow = row;
        hasLetterStart = true;
        symbolCount = 0;
      }

      if (duration < SHORT_BREAK_TIME_MS) {
        delay(10);
        lcd.print(".");
        currentLetter += ".";
        symbolCount++;
        advanceCursor(digit, row);
        lcd.setCursor(digit, row);
      } else if ((duration >= SHORT_BREAK_TIME_MS) && (duration < LONG_BREAK_TIME_MS)) {
        delay(10);
        lcd.print("-");
        currentLetter += "-";
        symbolCount++;
        advanceCursor(digit, row);
        lcd.setCursor(digit, row);
      }
    }
  }
  prevLedState = ledState;
}

void updateScreen() {
  if (!hasLetterStart || symbolCount == 0) return;

  eraseSymbols(startCol, startRow, symbolCount);

  lcd.setCursor(startCol, startRow);
  lcd.print(decodeMorse(currentLetter));

  digit = startCol;
  row = startRow;
  advanceCursor(digit, row);
  lcd.setCursor(digit, row);

  currentLetter = "";
  symbolCount = 0;
  hasLetterStart = false;
}
