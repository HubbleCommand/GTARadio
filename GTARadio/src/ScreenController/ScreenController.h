#pragma once
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class ScreenController{
public:
    ScreenController(uint8_t addr, int x, int y);
    void setup();
    void setText(String *text); //Set the text variable
    void setLine(int lineNo, String text);  //Set
    void setLineText(int lineNo, String text);
    void update();  //Used to auto scroll the screen, if needed
    
private:
    int x, y;
    String *text;
    LiquidCrystal_I2C* lcd; 
};