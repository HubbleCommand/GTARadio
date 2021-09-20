#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ScreenController.h"
#include "../defines.h"

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
    if(lineNo < this->y && lineNo > 0){   //Works, as y is total count of lines
        //this->lcd->setCursor(0, lineNo);
        //this->lcd->print(text);
        this->text[lineNo] = text;
        this->lcd->setCursor(0, lineNo);
        this->lcd->print(this->text[lineNo].substring(0,this->x));  //TODO check this actually works with x length of the screen
    }
    //We don't wanna go over...
}  

void ScreenController::update(){
    //this->lcd->scrollDisplayRight();
    this->lcd->clear();
    for(int i = 0; i < this->y; i++){
        this->lcd->setCursor(0,i);
        //this->lcd->print(this->text[i]);
        if(this->text[i].length() > this->x){
            String tmp = this->text[i].substring(0,(this->x - 1));
            tmp.concat(">");
            this->lcd->print(tmp);
        } else {
            this->lcd->print(this->text[i]);
        }
    }
}

void ScreenController::printStation(char* name){
    setLineUpdate(LCD_CHANNEL_LINE, name);
}

void ScreenController::printSong(char* name){
    setLineUpdate(LCD_SONG_LINE, name);
}

void ScreenController::printVolume(int volume){
    
}
