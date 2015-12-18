// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include <Wire.h>
#include <SPI.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <StarShipXP.h>

#define RS PF_1
#define EN PE_0
#define D4 PE_4
#define D5 PA_5
#define D6 PE_3
#define D7 PC_6

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

#define DHTPIN PB_2     // what pin we're connected to

#define DHTTYPE DHT11   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

unsigned int currentValue, previousValue=120, timeBase = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  lcd.begin(16,2);
  dht.begin();
  lcd.print(" Temp  Humidity");
  SPI.setModule(2);
  pinMode(GLCD_SEL1,OUTPUT);
  digitalWrite(GLCD_SEL1,HIGH);
  
  Tft.begin(GLCD_SEL2,GLCD_DC,PF_0,GLCD_RESET);
  Tft.TFTinit();
}

void loop() {
  delay(10);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  
  lcd.setCursor(1,1);
  lcd.print(t);
  
  lcd.setCursor(8,1);
  lcd.print(h);
 
  int potValue = analogRead(POT);
  currentValue = 235-(potValue/18); 
  Tft.fillRectangle(timeBase+1, 0, 3, 240, BLACK);
  Tft.drawLine(timeBase, previousValue, timeBase+1, currentValue, WHITE);
  previousValue = currentValue;
  timeBase = timeBase+1;
  
  if(timeBase > 315)
  {
    timeBase = 0;
    Tft.fillRectangle(0, 0, 3, 240, BLACK);
  }
}
