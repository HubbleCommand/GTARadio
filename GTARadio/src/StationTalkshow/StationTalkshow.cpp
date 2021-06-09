#include "StationTalkshow.h"

void StationTalkshow::play() {
    this->screen->setLineUpdate(1, this->name);
    if(this->intermission){
        if(this->situationalCounter <= 0){
            //We end the intermission
            this->intermission = false;
            
            //Play station ID
            this->playStationID();

            //Then the next loop, we will reach the outer else, play a talk, and once the talk is done then go to an intermission!
        } else {
            //We continue the intermission
            this->situationalCounter--;

            //However unlike Split stations, we don't really care which is played
            //We could also just play ads?
            if(random(2) > 1){
                this->playNews();
            } else {
                this->playAdvert();
            }
        }
    } else {
        //We want an intermission between each show!
        //So we set up the next intermission here
        this->situationalCounter = random(3,6);
        this->intermission = true;

        //Once the talk is finished, we will 

        char songSRCFolder[15];
        strcpy(songSRCFolder, this->source);
        strcat(songSRCFolder, "/MONO");
        int songCount = countTalks();
        int selSong = random(songCount);

        if(selSong == this->songID){
            selSong++;
            if(selSong > songCount){
                selSong = 0;
            }
        }

        this->songID = selSong;
        this->playTalk(this->songID);
    }
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
    int songCount = countTalks();

    if(this->songID < songCount - 1){
        this->songID++;
    } else {
        this->songID = 0;
    }
    
    this->playTalk(this->songID);
}

void StationTalkshow::prevSong() {
    this->stop();

    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/MONO");
    int songCount = countTalks();

    if(!(this->songID <= 0)){
        this->songID--;
    } else {
        this->songID = songCount - 1;
    }
    
    this->playTalk(this->songID);
}

void StationTalkshow::playStationID() {
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

void StationTalkshow::playTalk(int songID) {
    char namelov[22];
    strcpy(namelov, this->source);
    char tString[14];
    sprintf(tString, "/MONO/%i.wav", songID);
    strcat(namelov, tString);

    char songname[30];
    this->audio->listInfo(namelov, songname, 0);
    this->screen->setLineUpdate(2, songname);
    this->audio->play(namelov);
}

int StationTalkshow::countTalks(){
    if(this->talkCount == 0){
        char talkSRCFolder[15];
        strcpy(talkSRCFolder, this->source);
        strcat(talkSRCFolder, "/MONO");
        int tCount = countFiles(talkSRCFolder);
        this->talkCount = tCount;
        return this->talkCount;
    } else {
        return this->talkCount;
    }
}
