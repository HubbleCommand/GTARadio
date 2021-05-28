//#pragma once

#include <Arduino.h>
#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin, unsigned long increment){
    this->potPin = pin;
    this->potIncrement = increment;
}

int Potentiometer::getState(){
    return analogRead(this->potPin);
}

bool Potentiometer::stateChanged(){
    int reading = analogRead(this->potPin);
    
    if(abs(reading - this->lastPotState) > this->potIncrement){
        this->lastPotState = reading;
        return true;
    } else {
        return false;
    }
}