#pragma once
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class ScreenController{
public:
    ScreenController(uint8_t addr, int x, int y);
    void setup();                                   //Setup the LCD screen
    void setText(String *text);                     //Set the text variable
    void setLine(int lineNo, String text);          //Set the text for a specific line
    void setLineUpdate(int lineNo, String text);    //Set the text for a specific line & update the screen
    void update();                                  //Update the screen

private:
    int x, y;                   //Dimensions of the screen
    String *text;               //The text of the screen
    LiquidCrystal_I2C* lcd;     //Pointer to the actual controller
};