#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include "../ScreenController/ScreenController.h"
#include "../StationAbstract/StationAbstract.h"

class StationUnsplit : public StationAbstract {
public:
    using StationAbstract::StationAbstract;
    void nextSong();    //Play the next song
    void prevSong();    //Play the previous song

    void play();    //Will start playing station at a random time
    void stop();    //Stop playing the station
};