#include "StationSplit.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

StationSplit::StationSplit(char* name, char* source, TMRpcm* audio, ScreenController* screen) : StationAbstract(name, source, audio, screen){
    this->songCountDown = 6;
}

void StationSplit::play() {
    this->screen->setLine(1, this->name);
    if(this->introducingSong){
        introducingSong = false;
        this->songCountDown--;
        this->playSong(this->songID);
    } else if(this->intermission) {   //If we are in an intermission, then play it
        if(intermissionCounter <= 0){    //make sure that we end the itermission the next loop
            this->intermission = false;
            playStationID();
        } else {
            this->intermissionCounter--;
            if(this->news){
                playNews();
            } else {
                if(random(3)>2){
                    playHostSnippet();
                } else {
                    playAdvert();
                }
            }
        }
    } else {
        //Start intermission after a random number of songs have been played
        if(this->songCountDown <= 0){
            this->intermission = true;
            
            if(random(5 + 1) > 2){  //Play an ad
                this->news = false;
                this->intermissionCounter = random(3, 5 + 1); //Set a random number of intermission things to play
                playIntermissionIntro(true);
            } else {                //Play a news reel
                this->news = true;
                this->intermissionCounter = random(1, 3 + 1); //Set a random number of intermission things to play
                playIntermissionIntro(false);
            }
        } else {
            this->songCountDown = random(3,8);
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
            this->introducingSong = true;
            this->playTrackIntro(this->songID);
        }
    }
}

void StationSplit::stop() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->seconds = millis();
    this->audio->stopPlayback();
}

void StationSplit::nextSong() {
    this->intermission = false;
    this->stop();
    int songCount = countSongs();

    if(this->songID < this->songCount - 1){
        this->songID++;
    } else {
        this->songID = 0;
    }

    this->playSong(this->songID);
}

void StationSplit::prevSong() {
    this->intermission = false;
    this->stop();
    int songCount = countSongs();

    if(!(this->songID <= 0)){
        this->songID--;
    } else {
        this->songID = this->songCount - 1;
    }

    this->playSong(this->songID);
}

void StationSplit::playSong(int trackID) {
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

void StationSplit::playIntermissionIntro(bool advert) {
    if(advert){ //Play To Commercials bit
        char adIntroSRC[16 + 12];
        strcpy(adIntroSRC, this->source);
        strcat(adIntroSRC, "/TO/AD");
        int adIntroCount = countFiles(adIntroSRC);

        int introToPlay = random(1, adIntroCount + 1);
        char tString[12];
        sprintf(tString, "/TAD_%i.wav", introToPlay);
        strcat(adIntroSRC, tString);
        this->audio->play(adIntroSRC);
    } else {    //Play To News bit
        char newsIntroSRC[16 + 13];
        strcpy(newsIntroSRC, this->source);
        strcat(newsIntroSRC, "/TO/NEWS");
        int newsIntroCount = countFiles(newsIntroSRC);

        int introToPlay = random(1, newsIntroCount + 1);
        char tString[13];
        sprintf(tString, "/TNEW_%i.wav", introToPlay);
        strcat(newsIntroSRC, tString);
        this->audio->play(newsIntroSRC);
    }
}

void StationSplit::playStationID() {
    char idSRC[16 + 12];
    strcpy(idSRC, this->source);
    strcat(idSRC, "/ID");
    int idCount = countFiles(idSRC);

    int idToPlay = random(1, idCount + 1);
    char tString[12];
    sprintf(tString, "/ID_%i.wav", idToPlay);
    strcat(idSRC, tString);
    this->audio->play(idSRC);
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

void StationSplit::playHostSnippet(){
    char hostSRC[16 + 12];
    strcpy(hostSRC, this->source);
    strcat(hostSRC, "/HOST");
    int hostCount = countFiles(hostSRC);

    int hostToPlay = random(1, hostCount + 1);
    char tString[12];
    sprintf(tString, "/%i.wav", hostToPlay);
    strcat(hostSRC, tString);
    this->audio->play(hostSRC);
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
