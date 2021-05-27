//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//#include <StationController.h>
#include "src/Button/Button.h"
#include "src/Potentiometer/Potentiometer.h"
#include "src/ScreenController/ScreenController.h"

//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display //INGORE INTELLISENSE, it works...
ScreenController screen = ScreenController(0x3f,16,2);
Button buttonA = Button(2);
Button buttonB = Button(4);
Button buttonC = Button(7);
Button buttonD = Button(8);

String text2[2];

void setup()
{
    Serial.begin(9600);

    //lcd.init();                      // initialize the lcd 
    //lcd.backlight();
    screen.setup();

    text2[0] = ("Hello, world!");
    text2[1] = ("Ywrobot Arduino!");

    buttonA.setup();
    buttonB.setup();
    buttonC.setup();
    buttonD.setup();
}

void loop()
{
    if(buttonA.stateChanged()){
        text2[0] = "A";
        Serial.println("A");
    }
    if(buttonB.stateChanged()){
        text2[0] = "B";
        Serial.println("B");
    }
    if(buttonC.stateChanged()){
        text2[0] = "C";
        Serial.println("C");
    }
    if(buttonD.stateChanged()){
        text2[0] = "D";
        Serial.println("D");
    }

    /*if(volumeController.stateChanged()){
        int volume = volumeController.getState();
        text2[1] = volume;
        Serial.println(volume);
    }*/

    //int val = analogRead(A5);
    //Serial.println(val);

    for(int i = 0; i < 2; i++){
        //lcd.setCursor(0,i);
        //lcd.print(text2[i]);
        screen.setLine(i, text2[i]);
    }
}