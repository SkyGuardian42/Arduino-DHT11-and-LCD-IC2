/*  Made by: SkyGuardian42
 *  Started: 06.11.15
 *  CONNECTIONS:
 *  
 *  DHT11:
 *  -GND to GND
 *  -DATA to Digital Pin 8
 *  -VCC to 5V
 *  
 *  LCD with IC2 Chip:
 *  -GND to GND
 *  -VCC to 5V  
 *  -SDA to Analog Pin 4
 *  -SCL to Analog Pin 5
 */

 
//J.A.R.V.I.S Version
const char ver[] = "3.0";

//DHT Library by ladyada
//Source https://github.com/adafruit/DHT-sensor-library
#include "DHT.h"

//New LiquidCrystal Lybrary by fmalpartida
//Source https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//DHT Type and Pin
#define DHTPIN 8            //pin connected to the DHT11
#define DHTTYPE DHT11       //define DHT type

// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

//Define the LCD Pins and IC2 Adress
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

int pos = 0;               //position of the text

unsigned long currentMillis = 0;             //current milliseconds
const long interval = 4500;                  //time between the cycle of the lower LCD
unsigned long previousMillis = interval;     //time since the last cycle of the LCD

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
void clearLCD() {               //Clear the lower Screen
    lcd.setCursor(0, 1);
  lcd.print("                ");   
}
void setup() {
  dht.begin();                   // initialize the dht
  lcd.setBacklightPin(3,POSITIVE);
  lcd.begin(16,2);               // initialize the lcd 
  lcd.createChar(0, Degrees);
  lcd.createChar(1, Percent);
  
  pinMode(ledPin, OUTPUT);    // initialize the LED pin as an output
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input
  
  //Print Jarvis Version on top
  lcd.setCursor (0, 0);
  lcd.print("J.A.R.V.I.S");
  lcd.print(" v");
  lcd.print(ver);
}

void loop() {
    
  currentMillis = millis();

  buttonState = digitalRead(buttonPin);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();           //read humidity in Percent
  int t = dht.readTemperature();        //read temperature as Celsius



  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  if (currentMillis - previousMillis >= interval){
    
    previousMillis = currentMillis;     //time since last cycle
      
    switch (pos) {                      //Cycling through the different stages
      case 0:                           //Temperature
        clearLCD();
        pos = 1;
        lcd.setCursor (0, 1);
        lcd.print("Temperature: ");
        lcd.print(t);
        lcd.write(byte(0));   //Degrees
        break;
      case 1:                           //Humidity
        clearLCD();
        pos = 0;
        lcd.setCursor (0, 1);
        lcd.print("Humidity: ");
        lcd.print(h);
        lcd.write(byte(1));   //Percent
        break;
   }

  }
}
