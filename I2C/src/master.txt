#include <Arduino.h>
#include <Wire.h>

#define SLAVE1 0x01

void setup(){
    Wire.begin();
}

void loop(){
    Wire.beginTransmission(SLAVE1);
    Wire.write("Dices");
    Wire.endTransmission();
}