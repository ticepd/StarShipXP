/*
    LM75 - An arduino library for the LM75 temperature sensor
    Copyright (C) 2011  Dan Fekete <thefekete AT gmail DOT com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Wire.h>
#include <SPI.h>
#include <LM75.h>

LM75 sensor;  // initialize an LM75 object
// You can also initiate with another address as follows:
//LM75 sensor(LM75_ADDRESS | 0b001);  // if A0->GND, A1->GND and A2->Vcc

void setup()
{
  Wire.setModule(1);
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  // get temperature from sensor
  Serial.print("Current temp: ");
  Serial.print(sensor.temp());
  Serial.println(" C");
  
  // Tos Set-point
  sensor.tos(41.5); // set at 47.5'C
  Serial.print("Tos set at ");
  Serial.print(sensor.tos());
  Serial.println(" C");
  
  // Thyst Set-point
  sensor.thyst(50.2); // set at 42'C
  Serial.print("Thyst set at ");
  Serial.print(sensor.thyst());
  Serial.println(" C");
  
  // shutdown the sensor and wait a while
  sensor.shutdown(true);
  delay(3000);
  // wake up sensor for next time around
  sensor.shutdown(false);
  
  Serial.println();
}
