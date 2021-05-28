#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ScreenController.h"

ScreenController::ScreenController(uint8_t addr, int x, int y){
    this->x = x;
    this->y = y;
    this->lcd = new LiquidCrystal_I2C(addr, x, y);  //INGORE INTELLISENSE, it works...
}

void ScreenController::setup(){
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->setCursor(0,0);
    this->lcd->print("BOO");
    this->lcd->scrollDisplayRight();
}

void ScreenController::setLine(int lineNo, String text){
    this->lcd->setCursor(0, lineNo);
    //this->lcd->print("                    "); //THIS LINE CAUSES TROUBLE; JUST USE CLEAR!
    this->lcd->print(text);
}

void ScreenController::update(){
    this->lcd->clear();
    for(int i = 0; i < 2; i++){
        this->lcd->setCursor(0,i);
        this->lcd->print(this->text[i]);
    }
}