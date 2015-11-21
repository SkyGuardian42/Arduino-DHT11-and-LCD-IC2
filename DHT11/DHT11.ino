#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

#define DHT11_PIN 8

byte Degrees[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte Percent[8] = {
  B00000,
  B11000,
  B11001,
  B00010,
  B00100,
  B01011,
  B10011,
};

void clearLcd() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void setup(){
  Serial.begin(9600);
  Serial.print("LIBRARY VERSION: ");
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");

  lcd.setBacklightPin(3,POSITIVE);
  lcd.begin(16, 2);
  lcd.createChar(0, Degrees);
  lcd.createChar(1, Percent);
}

void loop(){
  lcd.home ();                   // go home
  lcd.print("Hello, ARDUINO ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" WORLD!  ");    

  delay(1000);
}

