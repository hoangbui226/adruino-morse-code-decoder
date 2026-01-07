#include <Arduino.h>
#include "app_state.h"
#include "app_config.h"
#include "lcd_ui.h"

void advanceCursor(int &c, int &r) {
  c++;
  if (c >= LCD_COLS) {
    c = 0;
    r++;
    if (r > (LCD_ROWS - 1)) {
      r = 0;
      lcd.clear();
    }
  }
}

void eraseSymbols(int startC, int startR, int count) {
  int c = startC;
  int r = startR;
  for (int i = 0; i < count; i++) {
    lcd.setCursor(c, r);
    lcd.print(" ");
    advanceCursor(c, r);
  }
}
