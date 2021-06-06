#include "StationUnsplit.h"

void StationUnsplit::play() {
    this->screen->setLine(1, this->name);
    char trackSRC[18];
    strcpy(trackSRC, this->source);
    strcat(trackSRC, "/SRC.wav");

    if(this->seconds > 0){
        this->audio->play(trackSRC, millis() - this->seconds);   //TODO check if need to handle seekpoint being longer than the track duration
    } else {
        float duration = getTrackDuration(trackSRC);
        int randomStart = random((int) duration);

        this->audio->play(trackSRC, randomStart);
    }
    this->screen->setLine(2, "");
    this->audio->loop(1);
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
    //NOTHING TO DO
}

void StationUnsplit::prevSong() {
    //NOTHING TO DO
}