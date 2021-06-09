#include "StationTalkshow.h"

//TODO play() and cont() can actually be merged...

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

    this->intermission = true;
    this->situationalCounter = random(3,6);
    
    char songSRCFolder[15];
    strcpy(songSRCFolder, this->source);
    strcat(songSRCFolder, "/MONO");
    //int songCount = countFiles(songSRCFolder);
    int songCount = countTalks();
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
        //int songCount = countFiles(songSRCFolder);
        int songCount = countTalks();
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
    //int songCount = countFiles(songSRCFolder);
    int songCount = countTalks();

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
    //int songCount = countFiles(songSRCFolder);
    int songCount = countTalks();

    if(!(this->songID <= 0)){
        this->songID--;
    } else {
        this->songID = songCount - 1;
    }
    
    this->play(this->songID);
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
