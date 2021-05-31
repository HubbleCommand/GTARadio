#include "StationUnsplit.h"

void StationUnsplit::play() {
    this->audio->disable();
    this->audio->play(this->source);
    //return source + "/SRC.wav";
}

void StationUnsplit::nextSong() {
    countFiles((char*) "ABC");
}

void StationUnsplit::prevSong() {

}