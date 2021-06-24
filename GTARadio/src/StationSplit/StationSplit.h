#include "../StationAbstract/StationAbstract.h"

class StationSplit : public StationAbstract {
public:
    StationSplit(char* name, char* source, TMRpcm* audio, ScreenController* screen);    //Uses custom constructor for setting some variables
    void nextSong();    //Play the next song
    void prevSong();    //Play the previous song
    void play();
    void stop();
private:
    void playSong(int trackID);
    void playTrackIntro(int trackID);
    int countSongs();
    char songCount = 0;

    //Host audio stuff
    int hostCount = 0;
    void playHostSnippet();

    //Song intro stuff
    bool introducingSong = false;   //If the station was prviously introducing a song
    bool findSongIntro(int number, int trackID);

    //Intermission (advert / news / maybe GTA IV weather) stuff
    void playIntermissionIntro(bool advert);
    void playStationID();   //Played at the end of the intermission

    int songCountDown = 0;
    int intermissionCounter; //Used for counting down the ads / news reels to play
    bool intermission = false;  //if the station is actively playing news or ads
    bool news;     //if the intermission being played is news (if false, then is ads)
};