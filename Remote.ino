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

#define button 2                    // button pin

RF24 radio(7, 8);                   // Nano CE & CSN pins

const byte address[6] = "00001";    // radio channel

boolean buttonState = 1;            // button state (1 = not pressed)

void setup() {
  pinMode(button, INPUT_PULLUP);    // setup button pin
  
  radio.begin();                    // start radio
  radio.openWritingPipe(address);   // open channel
  radio.setPALevel(RF24_PA_MIN);    // set power to min
  radio.stopListening();            // prepare to transmit
}

void loop() {
  buttonState = digitalRead(button);// check button
  if (buttonState == LOW) {         // if button pressed
    radio.write(&buttonState, sizeof(buttonState)); // transmit button press
    delay(1000);                    // debounce button
  }
  delay(10);                        // pause 1/100th second
}
