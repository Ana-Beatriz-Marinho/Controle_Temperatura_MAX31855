#include <SPI.h>
#include "max6675.h"
#include "Adafruit_MAX31855.h"

#define MAXDO   2
#define MAXCS1  13  //MAX31855
#define MAXCS2  4   //MAX6675
#define MAXCLK  18

Adafruit_MAX31855 termopar_31855(MAXCLK, MAXCS1, MAXDO);
MAX6675 termopar_6675(MAXCLK, MAXCS2, MAXDO);

void setup() {
  Serial.begin(9600);
  pinMode(32, OUTPUT);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  //Serial.print("Initializing sensor...");
  if (!termopar_31855.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }
  Serial.println("DONE.");
}

void loop() {

   double c_31855 = termopar_31855.readCelsius();

   if (isnan(c_31855)) {
     Serial.println("Problema");
   } else {
     Serial.print("Temperatura (°C) = ");
     Serial.println(c_31855);
    
     if(c_31855 > -120){
    digitalWrite(32,HIGH);
    Serial.println("Válvula Aberta");
    }else{
      digitalWrite(32,LOW);
      Serial.println("Válvula Fechada");
      }
   }

   delay(1000);
}
