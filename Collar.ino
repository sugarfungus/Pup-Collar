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

#define red 9                       // red led pin
#define green 10                    // green led pin
#define piezo 2                     // buzzer pin

RF24 radio(7, 8);                   // Nano CE & CSN pins

const byte address[6] = "00001";    // radio channel

boolean buttonState = 1;            // button state (1 = not pressed)

void setup() {
  pinMode(piezo, OUTPUT);           // setup buzzer pin
  pinMode(red, OUTPUT);             // setup red led pin
  pinMode(green, OUTPUT);           // setup green led pin
  digitalWrite(red, HIGH);          // turn off led (common anode)
  digitalWrite(green, HIGH);        // turn off led (common anode)
  
  radio.begin();                    // turn on raio
  radio.openReadingPipe(0, address);// open channel
  radio.setPALevel(RF24_PA_MIN);    // set power to min
  radio.startListening();           // prepare to receive
}

void loop() {
  if (radio.available()) {          // if signal present
      radio.read(&buttonState, sizeof(buttonState));// read button
      if (buttonState == LOW) {     // if button pressed
          digitalWrite(red, LOW);   // turn on red led
          analogWrite(green, 191);  // turn on green led
          tone(2, 500, 1000);       // sound buzzer
          delay(1000);              // wait one second 
          digitalWrite(red, HIGH);  // turn off led
          digitalWrite(green, HIGH);// turn off led
      }
  }
  delay(10);                        // pause 1/100th second
}

void rg(int r, int g) {             // write red & green leds
    analogWrite(red, 255 - r);      // write red led (common anode)
    analogWrite(green, 255 - g);    // write green led (common anode)
}

// fades two colors of an rgb led from the initial value to the final value, using the specified number
// of increments with the specified time interval, with a modifier to reduce the second color brightness
void doubleFade(int color1, int color2, int modifier, int initialVal, int finalVal, int increments, int fadeTime) {
    finalVal -= 255;                                            // correct for common anode
    initialVal -= 255;                                          // correct for common anode
    int incAmount = (finalVal - initialVal) / (increments - 1); // set size of increments
    analogWrite(color1, initialVal);                            // write first led start value
    analogWrite(color2, initialVal / modifier);                 // write second led start value using modifier
    delay(fadeTime);                                            // wait for specified time
    for (int i = 1; i < increments - 1; i++) {                  // for number of increments specified
        analogWrite(color1, initialVal + (incAmount * i));      // write first led
        analogWrite(color2, (initialVal + (incAmount * i)) / modifier); // write second led using modifier
        delay(fadeTime);                                        // wait for specified time
    }
    analogWrite(color1, finalVal);                              // write first led final value
    analogWrite(color2, finalVal / mod);                        // write second led final value using modifier
    delay(fadeTime);                                            // wait for specified time
}

void blink() {                      // blink leds twice then fade
    rg(255, 64);                    // write red and green to make amber
    delay(100);                     // wait 1/10th second
    rg(0, 0);                       // turn off leds
    delay(100);                     // wait 1/10th second
    doubleFade(red, green, 4, 255, 0, 40, 50); // write amber again then fade leds off
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
