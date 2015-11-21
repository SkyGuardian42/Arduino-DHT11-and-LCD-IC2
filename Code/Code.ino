/*
 * This uses the Liquid Crystal library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads GNU General Public License, version 3 (GPL-3.0)
 * Pin Connections: 
 *      SCL = A5
 *      SDA = A4
 *      VCC = 5V
 *      GND = GND
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);
    lcd.begin(16, 2);
}

void loop()
{
    lcd.setCursor(0,0);
    lcd.print("J.A.R.V.I.S  0.1");
    lcd.setCursor(0,1);
    long mil = millis();
    lcd.print(mil);
    delay(1000);
}
