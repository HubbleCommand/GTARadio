#pragma once
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include "../ScreenController/ScreenController.h"

class StationAbstract{
public:
    StationAbstract();
    StationAbstract(char* name, char* source, TMRpcm* audio, ScreenController* screen);
    virtual void nextSong() = 0;    //Play the next song
    virtual void prevSong() = 0;    //Play the previous song
    virtual void play() = 0;        //Will start playing station at a random time, used when first playing the station
    virtual void stop() = 0;        //Stop playing the radio station
    int countFiles(char* source);   //Count the files in a given directory
    void playAdvert();              //Play a random advertisement
    void playNews();                //Play a random news reel

    void printStationName();
    void printSongName(char* name);

    //Removed this function due to possible memory leaks
    //char* getTrackInfo(char* source, int infoID); //Refer to https://stackoverflow.com/questions/5660527/how-do-i-return-a-char-array-from-a-function/5660589
    float getTrackDuration(char* source);

    char* name, *source;            //Name & source path of the station
    TMRpcm* audio;                  //Pointer to the audio controller
    ScreenController* screen;       //Pointer to the screen controller

    int seconds;
    char songID;                    //The id of the currently playing song / the last song that stopped playing
};