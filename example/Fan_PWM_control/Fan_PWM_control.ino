/*
*********************************************************
Sample sketch for control fan with PWM pin(4-pin connectors) with 10K potentiometer and read RPM from fan
Data render to Serial port

USE WITH ARDUINO LEONARDO AND MICRO ONLY!!!
FOR OTHER MEGA328/2560 ARDUINAS USE THIS LIBRARY
http://code.google.com/p/arduino-pwm-frequency-library/downloads/list

****************************************************
*/

#include <Wire.h>
#include <PWM_32U4.h>

#include <SheduledEvent.h>
//download link: https://github.com/NailAlex/SheduledEvent

unsigned long previousRPMMillis;
unsigned long previousMillis;
float RPM;

SheduledEvent uEvent, Render;
 
unsigned long interval = 1000;
byte pwmValue = 125;
byte pwmInterval = 5;
const byte pwmMax = 255;
const byte pwmMin = 0;

//Connect cental pin of 10K potentiometer to A0
//Connect tacho pin from fan to D2
//Connect PWM pin from fan to D9
#define tachoPin 2
#define fanPin  9
#define handlePin A0
 
volatile unsigned long pulses=0;
unsigned long lastRPMmillis = 0;
 
void countPulse() {
  // just count each pulse we see
  // ISRs should be short, not like
  // these comments, which are long.
  pulses++;
}

 
void setup() {
  Serial.begin(115200);
  //initialize all timers except for 0, to save time keeping functions

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);    
  
    pinMode(tachoPin,INPUT_PULLUP);
    pinMode(handlePin,INPUT);
    attachInterrupt(digitalPinToInterrupt(tachoPin), countPulse, FALLING);
    pinMode(fanPin, OUTPUT); // probably PWM
    
    uEvent.SetEvent(0,200,handleManual,EVENT_CYCLED);
    uEvent.Start();
    Render.SetEvent(0,1000,Renderer,EVENT_CYCLED);
    Render.Start();

    pwm613configure(PWM23k);
    pwmSet6(0);

}
 
unsigned long calculateRPM() {
  unsigned long RPM;
  noInterrupts();
  float elapsedMS = (millis() - lastRPMmillis)/1000.0;
  unsigned long revolutions = pulses/2;
  RPM = (revolutions / elapsedMS) * 60.0;
  lastRPMmillis = millis();
  pulses=0;
  interrupts();
  return RPM;
}

void handleManual() {
 int val = analogRead(handlePin);
 pwmValue = map(val,0,1023,0,255);
 pwmWrite6(pwmValue);
}

void Renderer() {
    Serial.print("RPM=");
    Serial.print(calculateRPM());
    Serial.print(" @ PWM=");
    Serial.println(pwmValue);
}

 
void loop() {
  uEvent.Update();
  Render.Update();
}
 

