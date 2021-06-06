#include <SD.h>
#include "StationAbstract.h"

StationAbstract::StationAbstract() {}
StationAbstract::StationAbstract(char* name, char* source, TMRpcm* audio, ScreenController* screen) {
    this->name = name;
    this->source = source;
    this->audio = audio;
    this->screen = screen;

    this->songID = -1;
    this->seconds = -1;
}

int StationAbstract::countFiles(char* source){
    int count = 0;

    File  dir = SD.open(source);
    while(true){
        File entry =  dir.openNextFile();
        if (! entry) {break;}// no more files

        if (entry.isDirectory()) {

        } else {
            count++;
            this->screen->setLine(2, String(count));
        }

        entry.close();
    }
    return count;
}

//MAKE SURE TO DEALLOCATE THE SPACE USED BY PERSISTENT WHEN USING THIS FUNCTION!
char* StationAbstract::getTrackInfo(char* source, int infoID){  //0 - Track Name, 1 - Artist name
    char* persistent = malloc(50);
    this->audio->listInfo(source, persistent, infoID);
    return persistent;
}

float StationAbstract::getTrackDuration(char* source){
    //Taken from https://github.com/TMRh20/TMRpcm/issues/141
    File sourceFile = SD.open(source);

    if(sourceFile){
        sourceFile.seek(24);
        uint32_t sampleRate = 0;
        uint32_t fileSize = 0;
        float lengthInSeconds = 0.00;

        sampleRate = sourceFile.read();
        sampleRate |= (uint32_t)(sourceFile.read() << 8);
        sampleRate |= (uint32_t)(sourceFile.read() << 16);
        sampleRate |= (uint32_t)(sourceFile.read() << 24);
        fileSize = sourceFile.size()-44;
        lengthInSeconds = (float)(fileSize) / (float)(sampleRate) ;
        sourceFile.close();

        return lengthInSeconds;
    } else {
        return -1;
    }
}

void StationAbstract::playAdvert(){
    char nameAd[13];
    //There are a total of 96 ads (in GTA V), so generate a number to get
    int selAd = random(185); 
    sprintf(nameAd, "ADS/%i.wav", selAd);
    this->audio->play(nameAd);
}

void StationAbstract::playNews(){
    char nameNews[14];
    //There are a total of 107 news lines (in GTA V), so generate a number to get
    int selNews = random(177);
    sprintf(nameNews, "NEWS/%i.wav", selNews);
    this->audio->play(nameNews);
}