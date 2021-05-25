//#pragma once

#include <Arduino.h>
#include "Button.h"

Button::Button(int pin){
    this->buttonPin = pin;
}

void Button::setup(){
    pinMode(this->buttonPin, INPUT);
}

bool Button::stateChanged(){
    int reading = digitalRead(this->buttonPin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != this->lastButtonState) {
        // reset the debouncing timer
        this->lastDebounceTime = millis();
    }

    if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != this->buttonState) {
            this->buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (this->buttonState == HIGH) {
                //ledState = !ledState;
                this->lastButtonState = reading;
                return true;
            }
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    this->lastButtonState = reading;
    return false;
}