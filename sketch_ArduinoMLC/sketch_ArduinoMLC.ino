/**
  *  ArduinoMLC - Magic Life Counter
  *  
  *  Authors:  Fernando Concatto (GitHub:concatto)
  *            João Felipe Gonçalves (GitHub:jfrode)
  */


#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Players score
int player1 = 20;
int player2 = 20;

int who = 1;

// Buttons declaration
int buttonAdd = 8;
int buttonSub = 9;
int buttonSwitch = 10;

// Buttons states
boolean pressedAdd = false;
boolean pressedSub = false;
boolean pressedSwitch = false;


void setup() {
  lcd.begin(16, 2);
  pinMode(buttonAdd, INPUT);
  pinMode(buttonSub, INPUT);
  pinMode(buttonSwitch, INPUT);
  reprint();
}
 
void loop() { 
  if (digitalRead(buttonSwitch) == HIGH) {
    if (!pressedSwitch) {
      if (who == 1) {
        who = 2;
      } else {
        who = 1;
      }
      pressedSwitch = true;
    }
  } else {
    pressedSwitch = false;
  }
  
  if (digitalRead(buttonAdd) == HIGH) {
    if (!pressedAdd) {
      if (who == 1) {
        player1 = player1 + 1;
      } else {
        player2 = player2 + 1;
      }
      reprint();
      pressedAdd = true;
    }
  } else {
    pressedAdd = false;
  }
  
  if (digitalRead(buttonSub) == HIGH) {
    if (!pressedSub) {
      if (who == 1) {
        player1 = player1 - 1;
      } else {
        player2 = player2 - 1;
      }
      reprint();
      pressedSub = true;
    }
  } else {
    pressedSub = false;
  }
}

void reprint() {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(player1);
  
  lcd.setCursor(0, 1);
  lcd.print(player2);
}
