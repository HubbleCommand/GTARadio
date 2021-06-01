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
const char* src0 = "/SRC.wav";
const int advCount PROGMEM = 96;
const int newsCount PROGMEM = 107;

TMRpcm tmrpcm;
ScreenController screen = ScreenController(0x27,20,4);    //0x27 for 20x4, 0x3f for 16x2
Button butNextStation = Button(2);
Button butPrevStation = Button(3);

struct Station {
    const char source [9]; //While it can be smaller, this is easy
    const char* name;
    char type; //0 - Unsplit, 1 - Split, 2 - Talkshow   //char is used instead of int as it is 1 instead of 2 bytes
};

//Storing these strings takes a lot of space, so put them in FLASH instead of SRAM. No other memory management to do as it is flash and is reset on each powerup.
//TODO check wtf is going on here, only uses 2% of SRAM? Probably because struct uses pntrs, not the actual thing ? Still would take more space...
const Station stations[NUMBER_OF_STATIONS] /*PROGMEM*/ = {
    {"01_CROCK", "Classic Rock", 1},
    {"02_POP", "Non Stop Pop", 1},
    //{"03_HH_N", "Radio Los Santos", 1},
    //{"04_PUNK", "Channel X", 1},
    {"05_T1", "West Coast Talk Radio", 2},
    //{"06_CUNT", "Rebel Radio", 1},
    {"07_DAN1", "Soulwax FM", 0},
    {"08_MEX", "East Los FM", 0},
    //{"09_HH_0", "West Coast Classics", 1},
    //NO No10
    {"11_T2", "Blaine County Radio", 2},
    //{"12_REGG", "Blue Ark FM", 1},
    {"13_JAZZ", "WorldWide FM", 0},
    {"14_DAN2", "FlyLo FM", 0},
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

    tmrpcm.speakerPin = 9;
    tmrpcm.volume(0.5);
    tmrpcm.quality(1);
    selectedStationIndex = random(NUMBER_OF_STATIONS);   //DON't -1 ! the max is EXCLUSIVE
    handleStationChange(0);
    screen.setLine(0, "GTA Radio");
}

int audioLength(char* source){ //TODO check if need
    //https://github.com/TMRh20/TMRpcm/issues/141
}

int fileCount(char* source){
    File dir = SD.open(source);
    int count = 0;

    while(true){
        File entry =  dir.openNextFile();
        if(!entry){
            break;
        }

        if (entry.isDirectory()) {
            
        } else {
            count++;
        }

        entry.close();
    }

    return count;
}

void startType0(Station station){   //Unsplit
    tmrpcm.disable();
    screen.setLine(1, (char*)station.name);

    char* name_with_extension;
    name_with_extension = (char*) malloc(strlen(station.source)+1+8);
    strcpy(name_with_extension, station.source); 
    strcat(name_with_extension, src0);
    tmrpcm.play(name_with_extension, millis() / 1000);
    tmrpcm.loop(1);
    screen.setLine(2, name_with_extension);
    free(name_with_extension);
}

void startType1(Station station){   //Split
    tmrpcm.disable();
    screen.setLine(1, (char*)station.name);

    screen.setLine(2, "TODO");
}

void startType2(Station station){   //Talkshow
    tmrpcm.disable();
    screen.setLine(1, (char*)station.name);

    int selectedTalk = random(4);   //Both talkshow stations only have 4 monos, so good

    char* name_with_extension;
    name_with_extension = (char*) malloc(strlen(station.source)+1+10);
    strcpy(name_with_extension, station.source); 
    

    char* tmpString = new char[13];
    sprintf(tmpString, "/MONO/%i.wav", selectedTalk);

    strcat(name_with_extension, tmpString);

    tmrpcm.play(name_with_extension, millis() / 1000);
    tmrpcm.loop(1);

    //TODO printing info causes a crash
    //screen.setLine(2, name_with_extension);

    //char info[32];
	//tmrpcm.listInfo((char*)"RAIN.wav",info,0);
    //tmrpcm.listInfo(name_with_extension,info,0);
    //screen.setLine(2, info);

    free(name_with_extension);
    free(tmpString);
    //free(info);
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
    }
    if(butPrevStation.stateChanged()){
        handleStationChange(false);
    }

    int reading = analogRead(A0);
    if(abs(reading - lastPotState) > 10){
        lastPotState = reading;
        int volume = map(reading, 0, 1023, 0, 7);
        tmrpcm.setVolume(volume);

        char* tmpString = new char[9];  //Needs to be 9
        sprintf(tmpString, "VOL :  %i", volume);
        screen.setLine(LCD_VOL_LINE, tmpString);
        free(tmpString);
    }
}
