#include "StationSplit.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//TODO make cont() and play() the same function? they should both really do the same thing...
void StationSplit::play() {
    this->screen->setLine(1, this->name);

    /*char songSRC[15];
    strcpy(songSRC, this->source);
    strcat(songSRC, "/SONGS");
    int songCount = countFiles(songSRC);
    int selSong = random(songCount);*/

    /*int songCount = countSongs();
    int selSong = random(songCount);

    this->songID = selSong;
    this->play(this->songID);*/
    this->cont();
}

void StationSplit::cont() {
    /*char songSRC[15];
    strcpy(songSRC, this->source);
    strcat(songSRC, "/SONGS");
    int songCount = countFiles(songSRC);
    this->songCount = songCount;
    int selSong = random(this->songCount);*/

    if(introducingSong){
        introducingSong = false;
        this->play(this->songID);
    } else {
        int songCount = countSongs();
        int selSong = random(songCount);

        if(selSong == this->songID){
            selSong++;
            if(selSong > this->songCount){
                selSong = 0;
            }
        }

        this->songID = selSong;

        //ALWAYS play song intro, if it exists
        introducingSong = true;
        this->playTrackIntro(this->songID);
    }
}

void StationSplit::stop() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->seconds = millis();
    this->audio->stopPlayback();
}

void StationSplit::nextSong() {
    this->stop();
    
    /*char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/SONGS");
    int songCount = countFiles(songSRCFolder);

    this->songCount = songCount;*/
    int songCount = countSongs();

    if(this->songID < this->songCount - 1){
        this->songID++;
    } else {
        this->songID = 0;
    }

    this->play(this->songID);
}

void StationSplit::prevSong() {
    this->stop();

    /*char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/SONGS");
    int songCount = countFiles(songSRCFolder);

    this->songCount = songCount;*/
    int songCount = countSongs();

    if(!(this->songID <= 0)){
        this->songID--;
    } else {
        this->songID = this->songCount - 1;
    }

    this->play(this->songID);
}

void StationSplit::play(int trackID) {
    char trackSRC[22];
    strcpy(trackSRC, this->source);
    char tString[14];
    sprintf(tString, "/SONGS/%i.wav", trackID);
    strcat(trackSRC, tString);

    char songname[30];
    this->audio->listInfo(trackSRC, songname, 0);
    this->screen->setLine(2, songname);
    this->audio->play(trackSRC);
}

bool StationSplit::findSongIntro(int number, int trackID){
    char trackSRC[22];
    strcpy(trackSRC, this->source);
    char tString[16];
    sprintf(tString, "/INTRO/%i_%i.wav", trackID, number);
    strcat(trackSRC, tString);

    if(SD.exists(trackSRC)){
        return true;
    } else {
        return false;
    }
}

void StationSplit::playTrackIntro(int trackID) {
    int introCount = 1;

    while(findSongIntro(introCount, trackID)){
        introCount++;
    }

    int introToPlay = random(1,introCount);  //Max bounds is exclusive, so add 1, BUT AS introCount STARTS AT ONE WE DON'T NEED TO
    
    char trackSRC[22];
    strcpy(trackSRC, this->source);
    char tString[16];
    sprintf(tString, "/INTRO/%i_%i.wav", trackID, introToPlay);
    strcat(trackSRC, tString);
    this->audio->play(trackSRC);
}

int StationSplit::countSongs(){
    if(this->songCount == 0){
        char songSRCFolder[15];
        strcpy(songSRCFolder, this->source);
        strcat(songSRCFolder, "/SONGS");
        int songCount = countFiles(songSRCFolder);
        this->songCount = songCount;
        return this->songCount;
    } else {
        return this->songCount;
    }
}
