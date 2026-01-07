#include <Arduino.h>
#include "morse_decoder.h"

char decodeMorse(String code) {
  String morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
  char letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  for (int i = 0; i < 26; i++) {
    if (code == morse[i]) return letters[i];
  }
  return '?';
}
