/*
 * Arduino morse code decoder
 * Build instructions (french) : https://www.mallorycoeur.com/posts/decoder-du-morse-avec-un-arduino
 * Mallory COEUR - 2016
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int input;
int tick = 10; // ms
int state;
String dictionnary[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String morse = "";
String translation = "";

void setup() {
  lcd.begin(16, 2);
  pinMode(13, INPUT); // button
}

void loop() {
  input = digitalRead(13);

  if (input == HIGH) {
    if (state <= 0)
      state = 0;
    state++;
  }
  else if (input == LOW) {
    if (state > 0) {
      if (state > 10)
        morse += "-";
      else
        morse += ".";
      state = 0;
    }
    state--;
  }
  
  if (state <= -30 && morse != "") 
  {
      translation += findInDictionnary(morse);
      morse = "";
      writeLine(0, "                ");
      writeLine(1, "                ");
  }

  writeLine(0, translation);
  writeLine(1, morse);
  delay(tick);
}

char findInDictionnary(String word) {
  for(int i = 0; i < 26; i++)
  {
    if (dictionnary[i] == word)
      return alphabet[i];
  }
  return false;
}

void writeLine(int line, String text)
{
  lcd.setCursor(0, line);
  lcd.print(text);
}

