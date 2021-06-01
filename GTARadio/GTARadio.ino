#include "src/Button/Button.h"
#include "src/ScreenController/ScreenController.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include <avr/pgmspace.h>   //For PROGMEM
#define SD_ChipSelectPin 4
#define NUMBER_OF_STATIONS 8
#define LCD_INTRO_LINE 0
#define LCD_CHANNEL_LINE 1
#define LCD_SONG_LINE 2
#define LCD_VOL_LINE 3

TMRpcm tmrpcm;
ScreenController screen = ScreenController(0x27,20,4);    //0x27 for 20x4, 0x3f for 16x2
Button butNextStation = Button(2);
Button butPrevStation = Button(3);

struct Station {
    const char* source; //While it can be smaller, this is easy
    const char* name;
    char type; //0 - Unsplit, 1 - Split, 2 - Talkshow   //char is used instead of int as it is 1 instead of 2 bytes
};

//Storing these strings takes a lot of space, so put them in FLASH instead of SRAM. No other memory management to do as it is flash and is reset on each powerup.
const Station stations[NUMBER_OF_STATIONS] PROGMEM = {
    {"01_CROCK", "Classic Rock", 1},
    {"02_POP", "Non Stop Pop", 1},
    //{"03_HH_N", "Radio Los Santos", 1},
    //{"04_PUNK", "Channel X", 1},
    {"05_T1", "West Coast Talk Radio", 2},
    //{"06_CUNT", "Rebel Radio", 1},
    {"07_DAN1/SRC.wav", "Soulwax FM", 0},
    {"08_MEX/SRC.wav", "East Los FM", 0},
    //{"09_HH_0", "West Coast Classics", 1},
    //NO No10
    {"11_T2", "Blaine County Radio", 2},
    //{"12_REGG", "Blue Ark FM", 1},
    {"13_JAZZ/SRC.wav", "WorldWide FM", 0},
    {"14_DAN2/SRC.wav", "FlyLo FM", 0},
    //{"15_MOTWN", "Low Down", 1},
    //{"16_SILAKE", "Radio Mirror Park", 1},
    //{"17_FUNK", "Space", 1},
    //{"18_90RCK", "Vinewood Boulevard Radio", 1},
};

int selectedStationIndex;

int lastPotState;

void setup()
{
    screen.setup();

    butNextStation.setup();
    butPrevStation.setup();

    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
        return;   // don't do anything more if not
    }

    char info[32];
	//tmrpcm.listInfo((char*)"RAIN.wav",info,0);
    //screen.setLine(2, info);

    tmrpcm.speakerPin = 9;
    tmrpcm.volume(0.5);
    tmrpcm.quality(1);
    //tmrpcm.play((char*)"NEWS/046.wav");
    //tmrpcm.play((char*)"01_CROCK/SONGS/ATTSS.wav");

    selectedStationIndex = random(0, NUMBER_OF_STATIONS - 1);
}

void audioLength(char* source){

}

void startType0(Station station){
    tmrpcm.disable();
    tmrpcm.play((char*)station.source);
    screen.setLine(2, station.name);
}

void startType1(Station station){
    screen.setLine(2, "TODO");
}

void startType2(Station station){
    screen.setLine(2, "TODO");
}

void handleStationChange(bool upOrDown){
    if(upOrDown){
        if(selectedStationIndex >= NUMBER_OF_STATIONS - 1){
            selectedStationIndex = 0;
        } else {
            selectedStationIndex++;
        }
        
    } else {
        if(selectedStationIndex <= 0){
            selectedStationIndex = NUMBER_OF_STATIONS - 1;
        } else {
            selectedStationIndex--;
        }
    }

    Station selectedStation = stations[selectedStationIndex];

    switch(selectedStation.type){
        case 0:
            startType0(selectedStation);
            break;
        case 1:
            startType1(selectedStation);
            break;
        case 2:
            startType2(selectedStation);
            break;
    }
}

void loop()
{
    if(!tmrpcm.isPlaying()){    //If no audio is playing, do something!
        //We could wrap this in a if(millis() % 1000 == 0), but isPlaying() is a very simple function that doesn't require any power, so no need (in fact wrapping it in the proposed function could be more intensive! A counter would be better)

    }

    if(butNextStation.stateChanged()){
        handleStationChange(true);

        screen.setLine(0, "A");
    }
    if(butPrevStation.stateChanged()){
        handleStationChange(false);

        screen.setLine(0, "B");
    }

    int reading = analogRead(A0);
    if(abs(reading - lastPotState) > 10){
        lastPotState = reading;
        int volume = map(reading, 0, 1023, 0, 7);
        tmrpcm.setVolume(volume);
        screen.setLine(1, "VOL : " + String(volume));
    }
}
