#include "StationUnsplit.h"

void StationUnsplit::play() {
    this->screen->setLine(1, this->name);
    //this->audio->play((char*)"13_JAZZ/SRC.wav");
    char trackSRC[18];
    strcpy(trackSRC, this->source);
    strcat(trackSRC, "/SRC.wav");
    
    //char tString[14];
    //sprintf(tString, "/SONGS/%i.wav", selSong);

    //this->audio->play(trackSRC, randomStart);
    if(this->seconds > 0){
        this->audio->play(trackSRC, millis() - this->seconds);   //TODO check if need to handle seekpoint being longer than the track duration
    } else {
        float duration = getTrackDuration(trackSRC);
        int randomStart = random((int) duration);

        this->audio->play(trackSRC, randomStart);
    }
    
    this->audio->loop(1);
    
    //return source + "/SRC.wav";
}

void StationUnsplit::cont() {
    //THIS SHOULD NEVER BE REACHED FOR THIS CLASS!!!    
}

void StationUnsplit::stop() {
    delay(1000);    //This delay seems to fix some audio bugs with tmrpcm
    this->seconds = millis();
    this->audio->loop(0);
    this->audio->stopPlayback();
}

void StationUnsplit::nextSong() {
    
}

void StationUnsplit::prevSong() {

}