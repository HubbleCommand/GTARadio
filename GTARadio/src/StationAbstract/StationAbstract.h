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
    virtual void nextSong() = 0;    //Play the next song
    virtual void prevSong() = 0;    //Play the previous song
    virtual void play() = 0;    //Will start playing station at a random time, used when first playing the station
    virtual void cont() = 0;    //Continue playing the station (i.e. when a song is over, play another one)
    virtual void stop() = 0;    //Stop playing the radio station
    //virtual void play(int startTime);   //Utility functions essentially...
    //virtual void play(char* song);
    //virtual void play(char* song, int startTime);
    int countFiles(char* source);
    void playAdvert();
    void playNews();

    char* getTrackInfo(char* source, int infoID);
    float getTrackDuration(char* source);

    char* name, *source;
    TMRpcm* audio;
    ScreenController* screen;

    int seconds;
    char songID;
    
private:
    

};