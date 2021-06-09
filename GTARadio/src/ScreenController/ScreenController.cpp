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

void ScreenController::setLineUpdate(int lineNo, String text){
    this->text[lineNo] = text;
    this->update();
}  

void ScreenController::setLine(int lineNo, String text){
    //this->lcd->setCursor(0, lineNo);
    //this->lcd->print(text);
    this->text[lineNo] = text;
    this->lcd->setCursor(0, lineNo);
    this->lcd->print(this->text[lineNo].substring(0,20));
}  

void ScreenController::update(){
    //this->lcd->scrollDisplayRight();
    this->lcd->clear();
    for(int i = 0; i < this->y; i++){
        this->lcd->setCursor(0,i);
        this->lcd->print(this->text[i]);
    }
}