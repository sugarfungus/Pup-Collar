/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define button 2

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

boolean buttonState = 1;

void setup() {
  pinMode(2, INPUT_PULLUP);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  buttonState = digitalRead(button);
  if (buttonState == LOW) {
    radio.write(&buttonState, sizeof(buttonState)); 
    delay(1000);   
  }
  delay(10);
}
