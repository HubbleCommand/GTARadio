#pragma once
#include "../StationAbstract/StationAbstract.h"

class StationTalkshow : public StationAbstract {
public:
    using StationAbstract::StationAbstract;
    void nextSong();    //Play the next song
    void prevSong();    //Play the previous song
    void play();
    void stop();
private:
    void play(int songID);

    //Song counting stuff
    int countTalks();
    char talkCount = 0;
    
    //There is no intermission intro or anything, only station ID!
    void playStationID();

    int situationalCounter; //Used for counting down the ads / news reels to play
    bool intermission;  //if the station is actively playing news or ads
};