/*
* Dog Collar Code
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

const int leds = 3;                 // led pin
const int piezo = 2;                // buzzer pin

RF24 radio(7, 8);                   // Nano CE & CSN pins

const byte address[6] = "00001";    // radio channel

int setting = 0;          // collar setting
int currentSetting = 0;

void setup() {
  pinMode(leds, OUTPUT);            // setup buzzer pin
  pinMode(piezo, OUTPUT);           // setup red led pin

  radio.begin();                    // turn on radio
  radio.openReadingPipe(0, address);// open channel
  radio.setPALevel(RF24_PA_MIN);    // set power to min
  radio.startListening();           // prepare to receive
}

void loop() {   
    if (currentSetting == 0) {
        digitalWrite(leds, LOW);        // turn off leds
        delay(1000);
    }
    if (currentSetting == 1) {
        digitalWrite(leds, LOW);        // turn off leds
        delay(1000);
    }
    if (currentSetting == 2) {   // if 
        flash();                 // blink led
        delay(2000);
    }
    if (currentSetting == 3) {   // if 
        steady();                // led on high
        delay(1000);
    }
    if (currentSetting == 4) {   // if 
        quickFlash();
        chirp();                // sound buzzer
    }
    else {
        if (!radio.available()) {
            quickFlash();
            chirp();
        }
    }
    delay(100);
    checkSetting();
}

void checkSetting(){                 // check check collar setting
    if (radio.available()) {        // if signal present
        radio.read(&setting, sizeof(setting));// read button
        if (currentSetting != setting) {
            currentSetting = setting;
        }
    }
}

void checkDelay(int ms) {           // delay while checking setting every 1/100th second
    int checks = ms / 10;           // divide delay milliseconds by 10
    for (int i = 0; i < checks; i++){ // for every 10 milliseconds
            checkSetting();          // check if button pressed
            delay(10);              // wait 10 milliseconds
    }
}

void fade() {                       // smoothly dim led from 255 to 0
    for (int i = 0; i < 52; i++) {  // in 52 steps
        analogWrite(leds, 255 - (5 * i)); // starting at 255, dim led by 5 each time
        delay(40);
    }
}

void flash(){                       // blink leds twice then fade
    digitalWrite(leds, HIGH);       // turn on leds
    delay(100);
    digitalWrite(leds, LOW);        // turn off leds
    delay(100);
    fade();                         // fade leds from 255 to 0
}

void quickFlash() {
    digitalWrite(leds, HIGH);       // turn on leds
    delay(100);
    digitalWrite(leds, LOW);        // turn off leds
    delay(100);
    digitalWrite(leds, HIGH);       // turn on leds
    delay(100);
    digitalWrite(leds, LOW);        // turn off leds
    delay(100);
    digitalWrite(leds, HIGH);       // turn on leds
    delay(100);
    digitalWrite(leds, LOW);        // turn off leds
    delay(100);
}

void steady() {
    digitalWrite(leds, HIGH);       // turn on leds
}
   
void chirp() {                      // sound buzzer three times quickly
    tone(piezo, 4000, 100);         // sound buzzer for 1/10th second
    delay(150);                     // wait
    noTone(piezo);                  // turn off buzzer
    tone(piezo, 3300, 100);         // sound buzzer for 1/10th second
    delay(150);                     // wait
    noTone(piezo);                  // turn off buzzer
    tone(piezo, 4000, 100);         // sound buzzer for 1/10th second
    delay(150);                     // wait
    noTone(piezo);                  // turn off buzzer
}
