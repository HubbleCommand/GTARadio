#include <SD.h>
#include "StationAbstract.h"

StationAbstract::StationAbstract() {

}

StationAbstract::StationAbstract(char* name, char* source, TMRpcm* audio, ScreenController* screen) {
    this->name = name;
    this->source = source;
    this->audio = audio;
    this->screen = screen;
}

void StationAbstract::nextSong(){}
void StationAbstract::prevSong(){}
void StationAbstract::play(){}

int StationAbstract::countFiles(char source[]){
    int count = 0;

    File  dir = SD.open(source);
    while(true){
        File entry =  dir.openNextFile();
        if (! entry) {break;}// no more files

        if (entry.isDirectory()) {

        } else {
            count++;
        }

        entry.close();
    }
    return count;
}