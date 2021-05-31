#pragma once
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include "../ScreenController/ScreenController.h"

//TODO use SD library to just dynamically load song paths (don't need to hard-code them... only radio station paths!)
class StationAbstract{
public:
    StationAbstract();
    StationAbstract(char* name, char* source, TMRpcm* audio, ScreenController* screen);
    virtual void nextSong();    //Play the next song
    virtual void prevSong();    //Play the previous song
    virtual void play();    //Will start playing station at a random time, used when first playing the station
    //virtual void play(int startTime);   //Utility functions essentially...
    //virtual void play(char* song);
    //virtual void play(char* song, int startTime);
    int countFiles(char source[]);
    char* name, *source;
    TMRpcm* audio;
    ScreenController* screen;
    
private:
    int seconds;

};