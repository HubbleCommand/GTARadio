#include "StationSplit.h"

void StationSplit::play() {
    this->screen->setLine(1, this->name);

    char songSRC[15];
    strcpy(songSRC, this->source);
    strcat(songSRC, "/SONGS");
    int songCount = countFiles(songSRC);
    int selSong = random(songCount);

    this->songID = selSong;
    this->play(this->songID);
}

void StationSplit::cont() {
    char songSRC[15];
    strcpy(songSRC, this->source);
    strcat(songSRC, "/SONGS");
    int songCount = countFiles(songSRC);
    int selSong = random(songCount);

    if(selSong == this->songID){
        selSong++;
        if(selSong > songCount){
            selSong = 0;
        }
    }

    this->songID = selSong;
    this->play(this->songID);
}

void StationSplit::stop() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->seconds = millis();
    this->audio->stopPlayback();
}

void StationSplit::nextSong() {
    this->stop();
    
    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/SONGS");
    int songCount = countFiles(songSRCFolder);

    if(this->songID < songCount - 1){
        this->songID++;
    } else {
        this->songID = 0;
    }

    this->play(this->songID);
}

void StationSplit::prevSong() {
    this->stop();

    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/SONGS");
    int songCount = countFiles(songSRCFolder);

    if(!(this->songID <= 0)){
        this->songID--;
    } else {
        this->songID = songCount - 1;
    }

    this->play(this->songID);
}

void StationSplit::play(int songID) {
    char trackSRC[22];
    strcpy(trackSRC, this->source);
    char tString[14];
    sprintf(tString, "/SONGS/%i.wav", songID);
    strcat(trackSRC, tString);

    char songname[30];
    this->audio->listInfo(trackSRC, songname, 0);
    this->screen->setLine(2, songname);
    this->audio->play(trackSRC);
}