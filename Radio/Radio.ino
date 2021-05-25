//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <StationController.h>
#include "src/Button/Button.h"


LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Button buttonA = Button(2);
Button buttonB = Button(4);
Button buttonC = Button(7);
Button buttonD = Button(8);

void setup()
{
    Serial.begin(9600);
    lcd.init();                      // initialize the lcd 
    lcd.init();
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(3,0);
    lcd.print("Hello, world!");
    lcd.setCursor(2,1);
    lcd.print("Ywrobot Arduino!");
    lcd.setCursor(0,2);
    lcd.print("Arduino LCM IIC 2004");
    lcd.setCursor(2,3);
    lcd.print("Power By Ec-yuan!");

    buttonA.setup();
    buttonB.setup();
    buttonC.setup();
    buttonD.setup();
}

void loop()
{
    if(buttonA.stateChanged()){
        lcd.clear();
        lcd.print("A");
        Serial.println("A");
    }
    if(buttonB.stateChanged()){
        lcd.clear();
        lcd.print("B");
        Serial.println("B");
    }
    if(buttonC.stateChanged()){
        lcd.clear();
        lcd.print("C");
        Serial.println("C");
    }
    if(buttonD.stateChanged()){
        lcd.clear();
        lcd.print("D");
        Serial.println("D");
    }
}