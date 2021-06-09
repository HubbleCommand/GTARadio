#include "../StationAbstract/StationAbstract.h"

class StationSplit : public StationAbstract {
public:
    using StationAbstract::StationAbstract;
    void nextSong();    //Play the next song
    void prevSong();    //Play the previous song
    void play();
    void cont();
    void stop();
private:
    void play(int trackID);
    void playTrackIntro(int trackID);
    int countSongs();
    char songCount = 0;

    //Host audio stuff
    int hostCount = 0;

    //Song intro stuff
    bool introducingSong = false;   //If the station was prviously introducing a song
    bool findSongIntro(int number, int trackID);
};