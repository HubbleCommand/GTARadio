#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ScreenController.h"

ScreenController::ScreenController(uint8_t addr, int x, int y){
    this->x = x;
    this->y = y;
    this->text = new String[y]; //Need to initialise strings here as empty, otherwise will be random and bug out the screen!
    this->lcd = new LiquidCrystal_I2C(addr, x, y);  //INGORE INTELLISENSE, it works...
}

void ScreenController::setup(){
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->setCursor(0,0);
    this->lcd->print("BOO");
    //this->lcd->scrollDisplayRight();
}

void ScreenController::setLineText(int lineNo, String text){
    this->text[lineNo] = text;
    update();
}  

void ScreenController::setLine(int lineNo, String text){
    //TODO text can sometimes overflow on the lines ABOVE! Set the classes' text variable, but only print the x amount of characters per line!
    //TODO check why this bug somehow fixed itself? Haven't seen it in a while...
    //this->lcd->setCursor(0, lineNo);
    //this->lcd->print(text);
    this->text[lineNo] = text;
    this->lcd->setCursor(0, lineNo);
    this->lcd->print(this->text[lineNo]);
}  

void ScreenController::update(){
    //this->lcd->scrollDisplayRight();
    this->lcd->clear();
    for(int i = 0; i < this->y; i++){
        this->lcd->setCursor(0,i);
        this->lcd->print(this->text[i]);
    }
}