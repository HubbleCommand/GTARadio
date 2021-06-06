#include "StationTalkshow.h"

void StationTalkshow::play() {
    this->screen->setLine(1, this->name);
    
    //Both talkshow stations only have 4 monos, so good
    //int selectedTalk = random(this->songCount - '0');   //- '0' easy conversion to int
    /*int selectedTalk = random(this->songCount);   //- '0' easy conversion to int

    char name_with_extension[22];
    strcpy(name_with_extension, this->source); 
    
    char tmpString[13];
    sprintf(tmpString, "/MONO/%i.wav", selectedTalk);

    strcat(name_with_extension, tmpString);*/

    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/MONO");
    int songCount = countFiles(songSRCFolder);
    int selSong = random(songCount);

    this->songID = selSong;
    this->play(this->songID);
    /*
    char songSRC[22];
    strcpy(songSRC, this->source);
    
    char tString[14];
    sprintf(tString, "/MONO/%i.wav", selSong);

    strcat(songSRC, tString);

    char songname[50];
    this->audio->listInfo(songSRC, songname, 0);
    this->screen->setLine(2, songname);

    this->audio->play(songSRC, millis() / 1000);*/
}

void StationTalkshow::cont() {
    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/MONO");
    int songCount = countFiles(songSRCFolder);
    int selSong = random(songCount);

    if(selSong == this->songID){
        selSong++;
        if(selSong > songCount){
            selSong = 0;
        }
    }

    this->songID = selSong;
    this->play(this->songID);
    /*
    char songSRC[22];
    strcpy(songSRC, this->source);
    
    char tString[14];
    sprintf(tString, "/MONO/%i.wav", selSong);

    strcat(songSRC, tString);

    char songname[50];
    this->audio->listInfo(songSRC, songname, 0);
    this->screen->setLine(2, songname);

    this->audio->play(songSRC);*/
}

void StationTalkshow::stop() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->seconds = millis();
    this->audio->stopPlayback();
}

void StationTalkshow::nextSong() {
    this->stop();

    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/MONO");
    int songCount = countFiles(songSRCFolder);

    if(this->songID < songCount - 1){
        this->songID++;
    } else {
        this->songID = 0;
    }
    
    this->play(this->songID);
}

void StationTalkshow::prevSong() {
    this->stop();

    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/MONO");
    int songCount = countFiles(songSRCFolder);

    if(!(this->songID <= 0)){
        this->songID--;
    } else {
        this->songID = songCount - 1;
    }
    
    this->play(this->songID);
}

void StationTalkshow::play(int songID) {
    char namelov[22];
    strcpy(namelov, this->source);
    char tString[14];
    sprintf(tString, "/MONO/%i.wav", songID);
    strcat(namelov, tString);

    char songname[30];
    this->audio->listInfo(namelov, songname, 0);
    this->screen->setLine(2, songname);
    this->audio->play(namelov);
}
