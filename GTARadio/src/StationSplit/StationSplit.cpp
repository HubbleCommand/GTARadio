#include "StationSplit.h"

void StationSplit::play() {
    this->screen->setLine(1, this->name);

    char songSRC[15];
    strcpy(songSRC, this->source);
    strcat(songSRC, "/SONGS");
    int songCount = countFiles(songSRC);
    int selSong = random(songCount);

    this->songID = selSong;

    char namelov[22];
    strcpy(namelov, this->source);
    
    char tString[14];
    sprintf(tString, "/SONGS/%i.wav", selSong);

    strcat(namelov, tString);
    //this->screen->setLine(2, namelov);

    char songname[30];
    this->audio->listInfo(namelov, songname, 0);
    this->screen->setLine(2, songname);

    this->audio->play(namelov);
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

    char namelov[22];
    strcpy(namelov, this->source);
    char tString[14];
    sprintf(tString, "/SONGS/%i.wav", selSong);
    strcat(namelov, tString);

    char songname[30];
    this->audio->listInfo(namelov, songname, 0);
    this->screen->setLine(2, songname);
    this->audio->play(namelov);
}

void StationSplit::stop() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->seconds = millis();
    this->audio->stopPlayback();
}

void StationSplit::nextSong() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->audio->stopPlayback();

    this->songID++;

    this->play(this->songID);
}

void StationSplit::prevSong() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->audio->stopPlayback();

    this->songID--;

    this->play(this->songID);
}

void StationSplit::play(int songID) {
    char namelov[22];
    strcpy(namelov, this->source);
    char tString[14];
    sprintf(tString, "/SONGS/%i.wav", songID);
    strcat(namelov, tString);

    char songname[30];
    this->audio->listInfo(namelov, songname, 0);
    this->screen->setLine(2, songname);
    this->audio->play(namelov);
}