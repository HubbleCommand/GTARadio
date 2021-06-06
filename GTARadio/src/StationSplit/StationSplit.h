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
    void play(int songID);

};