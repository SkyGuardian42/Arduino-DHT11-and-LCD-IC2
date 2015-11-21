// Written by ladyada, public domain
//Source https://github.com/adafruit/DHT-sensor-library
#include "DHT.h"

//New LiquidCrystal Lybrary by fmalpartida
//Source https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 8     // what digital pin we're connected to

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.print("DHT");
  Serial.print(DHTTYPE);
  Serial.println(" test!");
  dht.begin();                   // initialize the dht
  lcd.begin(16,2);               // initialize the lcd 
  lcd.setBacklightPin(3,POSITIVE);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  lcd.setCursor ( 0, 0 );                 // go home
  lcd.print("Hello, ARDUINO ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" WORLD!  ");    
}
