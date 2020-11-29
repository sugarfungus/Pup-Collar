/*

fade(int color, int initialVal, int finalVal, int increments, int fadeTime)

doubleFade(int color1, int color2, int initialVal, int finalVal, int increments, int fadeTime)

rgbFade(int initialVal, int finalVal, int increments, int fadeTime)

*/
    const int green = 9;
    const int blue = 10;
    const int red = 11;
    const int piezo = 0;
    
    int timing = 200;

void setup() {
  // put your setup code here, to run once:

    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(piezo, OUTPUT);
    
    //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

/*
    tone(piezo,4000, 100);
    delay(150);
    noTone(piezo);
    tone(piezo,3300, 100);
    delay(150);
    noTone(piezo);
    tone(piezo,4000, 100);
    delay(150);
    noTone(piezo);
    delay(1000);
*/

rgb(128,255,0);
delay(100);
rgb(0,0,0);
delay(100);
doubleFadeSpecial(green, red, 2, 255, 0, 40, 50);
delay(2000);
   
/*
    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 191);
    delay(timing/2);

    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    delay(timing/2);

    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 191);
    delay(timing);

    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 128);
    delay(timing);

    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 64);
    delay(timing);

    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 0);
    delay(timing);

    analogWrite(red, 191);
    analogWrite(green, 191);
    analogWrite(blue, 0);
    delay(timing);
    
    analogWrite(red, 191);
    analogWrite(green, 128);
    analogWrite(blue, 0);
    delay(timing);

    analogWrite(red, 128);
    analogWrite(green, 128);
    analogWrite(blue, 0);
    delay(timing);

    analogWrite(red, 128);
    analogWrite(green, 64);
    analogWrite(blue, 0);
    delay(timing);

    analogWrite(red, 64);
    analogWrite(green, 64);
    analogWrite(blue, 0);
    delay(timing);

    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    delay(timing*10);
*/
}

void rgb(int r, int g, int b) {
    analogWrite(red, r);
    analogWrite(green, g);
    analogWrite(blue, b);
}

void fade(int color, int initialVal, int finalVal, int increments, int fadeTime) {
    int incAmount = (finalVal - initialVal) / (increments - 1);
    analogWrite(color, initialVal);
    delay(fadeTime);
    for (int i = 1; i < increments - 1; i++) {
        analogWrite(color, initialVal + (incAmount * i));
        //Serial.println(initialVal + (incAmount * i));
        delay(fadeTime);
    }
    analogWrite(color, finalVal);
    delay(fadeTime);
}

void doubleFade(int color1, int color2, int initialVal, int finalVal, int increments, int fadeTime) {
    int incAmount = (finalVal - initialVal) / (increments - 1);
    analogWrite(color1, initialVal);
    analogWrite(color2, initialVal);
    delay(fadeTime);
    for (int i = 1; i < increments - 1; i++) {
        analogWrite(color1, initialVal + (incAmount * i));
        analogWrite(color2, initialVal + (incAmount * i));
        //Serial.println(initialVal + (incAmount * i));
        delay(fadeTime);
    }
    analogWrite(color1, finalVal);
    analogWrite(color2, finalVal);
    delay(fadeTime);
}

void rgbFade(int initialVal, int finalVal, int increments, int fadeTime) {
    int incAmount = (finalVal - initialVal) / (increments - 1);
    analogWrite(red, initialVal);
    analogWrite(green, initialVal);
    analogWrite(blue, initialVal);
    delay(fadeTime);
    for (int i = 1; i < increments - 1; i++) {
        analogWrite(red, initialVal + (incAmount * i));
        analogWrite(green, initialVal + (incAmount * i));
        analogWrite(blue, initialVal + (incAmount * i));
        //Serial.println(initialVal + (incAmount * i));
        delay(fadeTime);
    }
    analogWrite(red, finalVal);
    analogWrite(green, finalVal);
    analogWrite(blue, finalVal);
    delay(fadeTime);
}

void doubleFadeSpecial(int color1, int color2, int mod, int initialVal, int finalVal, int increments, int fadeTime) {
    int incAmount = (finalVal - initialVal) / (increments - 1);
    analogWrite(color1, initialVal);
    analogWrite(color2, initialVal / mod);
    delay(fadeTime);
    for (int i = 1; i < increments - 1; i++) {
        analogWrite(color1, initialVal + (incAmount * i));
        analogWrite(color2, (initialVal + (incAmount * i)) / mod);
        //Serial.println(initialVal + (incAmount * i));
        delay(fadeTime);
    }
    analogWrite(color1, finalVal);
    analogWrite(color2, finalVal / mod);
    delay(fadeTime);
}
