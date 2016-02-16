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
int manaPlayer1;
int manaPlayer2;

int who = 1;

// Buttons declaration
int buttonAdd = 8;
int buttonSub = 9;
int buttonSwitch = 10;

// Buttons states
boolean pressedAdd = false;
boolean pressedSub = false;
boolean pressedSwitch = false;

String manaNames[5] = {
  "White", "Blue", "Black", "Red", "Green"
};

byte manaCharacters[5][8] = {{
  // White
  B00000,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00000,
  B00000
}, {
  // Blue
  B01000,
  B00100,
  B01110,
  B11111,
  B11011,
  B11001,
  B01110,
  B00000
}, {
  // Black
  B00000,
  B01110,
  B10101,
  B10101,
  B11011,
  B01110,
  B10101,
  B00000
}, {
  // Red
  B01100,
  B00010,
  B00001,
  B01101,
  B11011,
  B11101,
  B10110,
  B01100
}, {
  // Green
  B01010,
  B10101,
  B01110,
  B10101,
  B01110,
  B00100,
  B00100,
  B00000
}};


void setup() {
  pinMode(buttonAdd, INPUT);
  pinMode(buttonSub, INPUT);
  pinMode(buttonSwitch, INPUT);
  lcd.begin(16, 2);
  for (int i = 0; i < 5; i++) lcd.createChar(i+1, manaCharacters[i]);
  introduction();
  manaChoosing();
  diceRoll();
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
  
  lcd.setCursor(5, 0);
  lcd.write(manaPlayer1);
  lcd.setCursor(7, 0);
  lcd.print(player1);
  lcd.setCursor(10, 0);
  lcd.write(manaPlayer1);
  
  lcd.setCursor(5, 1);
  lcd.write(manaPlayer2);
  lcd.setCursor(7, 1);
  lcd.print(player2);
  lcd.setCursor(10, 1);
  lcd.write(manaPlayer2);
}

void diceRoll() {
  
}

void manaChoosing() {
  manaPrint(0, 0);
  
  manaPlayer1 = manaSelect(0);
  manaPlayer2 = manaSelect(1);
  
  pressedAdd = false;
  pressedSub = false;
  pressedSwitch = false;
}

int manaSelect(int line) {
  int manaColor = 0;
  while(true) {
    if (digitalRead(buttonAdd) == HIGH) {
      if (!pressedAdd) {
        manaColor++;
        pressedAdd = true;
      }
      manaPrint(manaColor, line);
    } else {
      pressedAdd = false;
    }
    
    if (digitalRead(buttonSub) == HIGH) {
      if (!pressedSub) {
        manaColor--;
        pressedSub = true;
      }
      manaPrint(manaColor, line);
    } else {
      pressedSub = false;
    }
    
    if (digitalRead(buttonSwitch) == HIGH) {
      return manaColor;
    }
    
    if (manaColor > 4) manaColor = 0;
    if (manaColor < 0) manaColor = 4;
  }
}

void manaPrint(int manaColor, int line) {
  lcd.clear();
  
  lcd.setCursor(0, line);
  lcd.print("Player "); // <-
  lcd.print(line+1);    // How to concat?
  
  lcd.setCursor(9, line);
  lcd.write(manaColor + 1);
  
  lcd.setCursor(11, line);
  lcd.print(manaNames[manaColor]);
}

void introduction() {
  lcd.setCursor(0, 0);
  lcd.print("Concatto &");
  lcd.setCursor(7, 2);
  lcd.print("JFRode");
  delay(2500);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("MagicLifeCounter");
  lcd.setCursor(5, 1);
  for (int i=1; i <= 5; i++)  lcd.write(i);
  delay(3500);
}
