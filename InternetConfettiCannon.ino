/*************************************************************
Livestream interactive Confetti Cannon

This is one example of a platform-agnostic sketch that will allow audiences of live internet shows to interact with hardware, 
using Blynk, the movile phone IoT controller. In this case, we're allowing audiences to mash a button that raises a counter. 
When that counter reaches a predermined threshold, a relay is activated which then triggers the solenoid valve on an air cannon, 
blasting colored paper into the air. Of course, the idea here is that you can easily adapt the software and hardware so you can 
build whatever interactive hardware your show desires.

Tyler Winegarner, 2017


*/


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "[YOUR AUTH KEY HERE]";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "[WIFI SSID]";
char pass[] = "[WIFI PASSWORD]";

int blastPin = 12; //opens the relay
int releasePin = 14; //closes the relay
int buttonState = 5; //read the state of the Blynk button
int tick = -1; //Current counter state
int threshold = 100; //Threshold for the counter before the confetti is triggered


void setup()
{
  delay(500);
  // Debug console
  Serial.begin(9600);

  // Clear the buffer.
  pinMode(buttonState, INPUT);
  pinMode(blastPin, OUTPUT);
  pinMode(releasePin, OUTPUT);
  
 
 #ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);

  Blynk.begin(auth, ssid, pass);

}



void loop()
{
  // Release the Relay, just in case
  digitalWrite(releasePin, HIGH);
  delay(50);
  digitalWrite(releasePin, LOW);
  
  Blynk.run();

  // is the button being pressed?
  if (digitalRead(buttonState) == LOW) {
    tick++;
  }

  //Check to see if we've reached the threshold
  if (tick >= threshold) {

    //PREPARE FOR DRAMATIC ANIMATION
    for(int i = 0; i < 5; i++){
      matrix.println(tick);
      matrix.writeDisplay();
      delay(500);
      matrix.println(1000000);
      matrix.writeDisplay();
      delay(500);    
    }
      matrix.println(tick);
      matrix.writeDisplay();
      
    //COMMENCE FIRING SEQUENCE  
    digitalWrite(blastPin, HIGH);
    delay(50);
    digitalWrite(blastPin, LOW);
    delay(1000);
    digitalWrite(releasePin, HIGH);
    delay(50);
    digitalWrite(releasePin, LOW);
    while (tick) {
        tick--;
        matrix.println(tick);
        matrix.writeDisplay();
        delay(10);
    }
    // reset the clock
    tick = 0;
  }
    matrix.println(tick);
    matrix.writeDisplay();
}

