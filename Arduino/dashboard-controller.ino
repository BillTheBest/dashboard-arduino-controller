#include <Bounce2.h>
#include "rgbcolor.h"
#include "fader.h"

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
const int calibrationTime = 60;

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

boolean lockLow = true;
boolean takeLowTime;  

int pirPin = 7;    //the digital pin connected to the PIR sensor's output

int ledRedPin = 11;
int ledGreenPin = 10;
int ledBluePin = 9;

int button1 = 3;
int button2 = 2;
int button3 = 5;
int button4 = 4;

Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();
Bounce debouncer4 = Bounce();

Fader fader (ledRedPin, ledGreenPin,ledBluePin);

RGBColor yellow (200, 200,   0);
RGBColor red    (255,   0,   0);
RGBColor green  (  0, 100,   0);
RGBColor white  (255, 255, 255);
RGBColor black  (  0,   0,   0);
RGBColor blue   ( 0, 0, 210);
RGBColor orange (255,  30,  0);

void setLed(const RGBColor color) {
  analogWrite(ledRedPin, color.r());
  analogWrite(ledGreenPin, color.g());
  analogWrite(ledBluePin, color.b());
}

/////////////////////////////
//SETUP
void setup() {
    Serial.begin(9600);
    pinMode(pirPin, INPUT);
    digitalWrite(pirPin, LOW);

    pinMode(ledRedPin, OUTPUT);
    pinMode(ledGreenPin, OUTPUT);
    pinMode(ledBluePin, OUTPUT);

    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    pinMode(button4, INPUT_PULLUP);

    debouncer1.attach(button1);
    debouncer2.attach(button2);
    debouncer3.attach(button3);
    debouncer4.attach(button4);
    
    debouncer1.interval(5);
    debouncer2.interval(5);
    debouncer3.interval(5);
    debouncer4.interval(5);

    // Give the sensor some time to calibrate
    debug("calibrating sensor...");
    for (int i = 0; i < calibrationTime; i++) {
      if (i % 2 == 0) {
        fader.fade(red, yellow, 256, 5); // ~1 s
      } else {
        fader.fade(yellow, red, 256, 2); // !s
      }
      debug(String(calibrationTime - i));
    }
    
    debug("Done");
    debug("SENSOR ACTIVE");
    for (int i = 0; i < 3; i++) {
      setLed(black);
      delay(100);
      setLed(green);
      delay(100);
    }

    setLed(black);
    delay(500);
    setLed(blue);
}

////////////////////////////
//LOOP
void loop() {
    debouncer1.update();
    debouncer2.update();
    debouncer3.update();
    debouncer4.update();

    if (debouncer1.fell()) {
      setLed(orange);
      Serial.println("1");      
      delay(500);
      setLed(blue);
    }

    if (debouncer2.fell()) {
      setLed(orange);
      Serial.println("2");      
      delay(500);
      setLed(blue);
    }

    if (debouncer3.fell()) {
      setLed(orange);
      Serial.println("3");      
      delay(500);
      setLed(blue);
    }

    if (debouncer4.fell()) {
      setLed(orange);
      Serial.println("4");      
      delay(500);
      setLed(blue);
    }
  
    if (digitalRead(pirPin) == HIGH) {
       if (lockLow) {
           Serial.println("M");
           setLed(black);
           //makes sure we wait for a transition to LOW before any further output is made:
           lockLow = false;
           delay(150);
           setLed(blue);
       }         
       takeLowTime = true;
    }

    if (digitalRead(pirPin) == LOW) {
        if(takeLowTime){
            lowIn = millis();          //save the time of the transition from high to LOW
            takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       
        // If the sensor is low for more than the given pause, 
        // we assume that no more motion is going to happen
        if (!lockLow && millis()) {  
          // Makes sure this block of code is only executed again after 
          // a new motion sequence has been detected
          lockLow = true;
          Serial.println("E");
          delay(10);
        }
     }
}

void debug(const String& message) {
  Serial.println("D>" + message);
}
