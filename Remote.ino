/*
* Dog Collar Remote Code
* 
* by sugarfungus
* 
* Full project: https://github.com/sugarfungus/Pup-Collar
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int pot = A7;               // potentiometer pin

RF24 radio(7, 8);                   // Nano CE & CSN pins

const byte address[6] = "00001";    // radio channel

int reading = 0;          // potentiometer reading
int setting = 0;          // collar setting

void setup() {
  pinMode(pot, INPUT);    // setup button pin
  
  radio.begin();                    // start radio
  radio.openWritingPipe(address);   // open channel
  radio.setPALevel(RF24_PA_MIN);    // set power to min
  radio.stopListening();            // prepare to transmit

  Serial.begin(9600);
}

void loop() {
  reading = analogRead(pot);// check potentiometer
  setting = map(reading, 0, 1023, 4, 0);
  radio.write(&setting, sizeof(setting)); // transmit setting
  Serial.println(setting);
  delay(1000);
}
