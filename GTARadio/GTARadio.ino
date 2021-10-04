#include "src/Button/Button.h"
#include "src/ScreenController/ScreenController.h"
#include "src/StationAbstract/StationAbstract.h"
#include "src/StationSplit/StationSplit.h"
#include "src/StationUnsplit/StationUnsplit.h"
#include "src/StationTalkshow/StationTalkshow.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include <avr/pgmspace.h>   //For PROGMEM
#include "src/defines.h"

//This is really only intended to be used with a Mega, as TMRpcm requires lots of space when dealing with high sample rate audio

TMRpcm tmrpcm;
ScreenController screen = ScreenController(LCD_ADDR,LCD_X,LCD_Y);    //0x27 for 20x4, 0x3f for 16x2
Button butNextStation   = Button(44);
Button butPrevStation   = Button(45);
Button butNextSong      = Button(46);
Button butPrevSong      = Button(47);
Button butVolumUp       = Button(42);
Button butVolDown       = Button(43);

int selectedStationIndex;
int volumeG = 1;
int maxVolume = 5;

//GTA V Stations
StationSplit        CLASSIC_ROCK        = StationSplit((char*)"Los Santos Rock Radio", (char*)"01_CROCK", &tmrpcm, &screen);
StationSplit        NON_STOP_POP        = StationSplit((char*)"Non Stop Pop", (char*)"02_POP", &tmrpcm, &screen);
StationSplit        RADIO_LOS_SANTOS    = StationSplit((char*)"Radio Los Santos", (char*)"03_HH_N", &tmrpcm, &screen);
StationSplit        CHANNEL_X           = StationSplit((char*)"Channel X", (char*)"04_PUNK", &tmrpcm, &screen);
StationTalkshow     WCTR                = StationTalkshow((char*)"West Coast Talk Radio", (char*)"05_T1", &tmrpcm, &screen);
StationSplit        REBEL_RADIO         = StationSplit((char*)"Rebel Radio", (char*)"06_CUNT", &tmrpcm, &screen);
StationUnsplit      SOULWAX             = StationUnsplit((char*)"Soulwax FM", (char*)"07_DAN1", &tmrpcm, &screen);
StationUnsplit      ELS                 = StationUnsplit((char*)"East Los FM", (char*)"08_MEX", &tmrpcm, &screen);
StationSplit        WCC                 = StationSplit((char*)"West Coast Classics", (char*)"09_HH_O", &tmrpcm, &screen);
StationTalkshow     BLAINE_CR           = StationTalkshow((char*)"Blaine County Radio", (char*)"11_T2", &tmrpcm, &screen);
StationSplit        BLUE_ARK            = StationSplit((char*)"Blue Ark FM", (char*)"12_REGG", &tmrpcm, &screen);
StationUnsplit      WORLDWIDE           = StationUnsplit((char*)"WorldWide FM", (char*)"13_JAZZ", &tmrpcm, &screen);
StationUnsplit      FLY_LO              = StationUnsplit((char*)"FlyLo FM", (char*)"14_DAN2", &tmrpcm, &screen);
StationSplit        LOW_DOWN            = StationSplit((char*)"Low Down", (char*)"15_MTWN", &tmrpcm, &screen);
StationSplit        MIRROR_PARK         = StationSplit((char*)"Radio Mirror Park", (char*)"16_SILK", &tmrpcm, &screen);
StationSplit        SPACE               = StationSplit((char*)"Space", (char*)"17_FUNK", &tmrpcm, &screen);
StationSplit        VB_RADIO            = StationSplit((char*)"Vinewood Boulevard Radio", (char*)"18_90RK", &tmrpcm, &screen);

//GTA IV Stations
StationSplit        IF_99               = StationSplit((char*)"International Funk 99", (char*)"A_AFRO", &tmrpcm, &screen);
StationSplit        TUFF_GONG           = StationSplit((char*)"Tuff Gong Radio", (char*)"B_BBYLN", &tmrpcm, &screen);
StationUnsplit      THE_BEAT            = StationUnsplit((char*)"The Beat 102.7", (char*)"C_BEAT", &tmrpcm, &screen);
StationUnsplit      MASSIVE_B           = StationUnsplit((char*)"Massive B Soundsystem 96.9", (char*)"D_BK", &tmrpcm, &screen);
StationSplit        JOURNEY             = StationSplit((char*)"The Journey", (char*)"E_CLASS", &tmrpcm, &screen);
StationUnsplit      ELECTRO_CHOC        = StationUnsplit((char*)"Electro-Choc", (char*)"F_DANM", &tmrpcm, &screen);
StationSplit        RADIO_BROCKER       = StationSplit((char*)"Radio Brocker", (char*)"G_DANR", &tmrpcm, &screen);
//WTF 8? Just extra songs?
StationSplit        FUSION_FM           = StationSplit((char*)"Fusion FM", (char*)"H_FUS", &tmrpcm, &screen);
StationSplit        LC_HARD_CORE        = StationSplit((char*)"Liberty City Hard Core", (char*)"I_HARD", &tmrpcm, &screen);
//!!! CHANNEL 11 WAS MEANT FOR A USER-MADE RADIO STATION ON PC VERSIONS OF GTA IV !!!
StationSplit        JAZZ_NATION         = StationSplit((char*)"Jazz Nation Radio 108.5", (char*)"J_JAZZ", &tmrpcm, &screen);
StationSplit        K109                = StationSplit((char*)"K109 The Studio", (char*)"K_K109", &tmrpcm, &screen);
StationTalkshow     INTEGRITY           = StationTalkshow((char*)"Integrity 2.0", (char*)"L_LZLW", &tmrpcm, &screen);
StationSplit        LIBERTY_ROCK        = StationSplit((char*)"Liberty Rock Radio", (char*)"M_LIBR", &tmrpcm, &screen);
StationSplit        ACTUALIZATION       = StationSplit((char*)"Self-Actualization FM", (char*)"N_MED", &tmrpcm, &screen);
StationUnsplit      THE_CLASSICS        = StationUnsplit((char*)"The Classics 104.1", (char*)"O_NYCL", &tmrpcm, &screen);
StationTalkshow     PLR                 = StationTalkshow((char*)"Public Liberty Radio", (char*)"P_PLR", &tmrpcm, &screen);
StationUnsplit      RAMJAM              = StationUnsplit((char*)"RamJam FM", (char*)"Q_RJFM", &tmrpcm, &screen);
StationSplit        SAN_JUAN_SOUNDS     = StationSplit((char*)"San Juan Sounds", (char*)"R_SJS", &tmrpcm, &screen);
StationSplit        THE_VIBE            = StationSplit((char*)"The Vibe 98.8", (char*)"S_VIBE", &tmrpcm, &screen);
StationSplit        VCFM                = StationSplit((char*)"Vice City FM", (char*)"T_VCFM", &tmrpcm, &screen);
StationSplit        VLADIVOSTOK         = StationSplit((char*)"Vladivostok FM", (char*)"U_VLAD", &tmrpcm, &screen);
StationTalkshow     WKTT                = StationTalkshow((char*)"WKTT Radio", (char*)"V_WKTT", &tmrpcm, &screen);

StationAbstract* stationsCLASS[NUMBER_OF_STATIONS] = {
    &CLASSIC_ROCK, &NON_STOP_POP, &RADIO_LOS_SANTOS, &CHANNEL_X, &WCTR, &REBEL_RADIO, &SOULWAX, &ELS, &WCC, &BLAINE_CR, 
    &BLUE_ARK, &WORLDWIDE, &FLY_LO, &LOW_DOWN, &MIRROR_PARK, &SPACE, &VB_RADIO, &IF_99, &TUFF_GONG, &THE_BEAT, &MASSIVE_B, 
    &JOURNEY, &ELECTRO_CHOC, &RADIO_BROCKER, &FUSION_FM, &LC_HARD_CORE, &JAZZ_NATION, &K109, &INTEGRITY, &LIBERTY_ROCK, 
    &ACTUALIZATION, &THE_CLASSICS, &PLR, &RAMJAM, &SAN_JUAN_SOUNDS, &THE_VIBE, &VCFM, &VLADIVOSTOK, &WKTT,
};
//Needs to be array of pointers, as is Abstract class (would otherwise need to import std::vector)
//Can't use array of references obviously, as the data would be lost once out of scope

void setup()
{
    randomSeed(analogRead(A0) / analogRead(A1) + 1);

    screen.setup();
    butNextStation.setup();
    butPrevStation.setup();

    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
        screen.setLine(1, "SD ISSUE");
        return;   // don't do anything more if not
    } else {
        screen.setLine(0, "GTA Radio");
    }

    tmrpcm.speakerPin = TMRPCM_SPEAKER_PIN;
    tmrpcm.setVolume(.5);
    selectedStationIndex = random(NUMBER_OF_STATIONS);   //DON't -1 ! the max is EXCLUSIVE

    //Not updating the screen pointer AFTER THE SCREEN HAS BEEN SETUP causes issues
    /*for(int i = 0; i < NUMBER_OF_STATIONS; i++){
        stationsCLASS[i]->screen = &screen;
    }*/

    stationsCLASS[selectedStationIndex]->play();
}

void loop()
{    
    if(butNextStation.stateChanged()){
        changeStation(true);
    }

    if(butPrevStation.stateChanged()){
        changeStation(false);
    }

    if(butNextSong.stateChanged()){     //TODO check if increasing button debounce time fixed the total crash if next / prev song is pushed too soon
        stationsCLASS[selectedStationIndex]->nextSong();
    }

    if(butPrevSong.stateChanged()){
        stationsCLASS[selectedStationIndex]->prevSong();
    }

    if(butVolumUp.stateChanged()){
        changeVolume(true);
    }

    if(butVolDown.stateChanged()){
        changeVolume(false);
    }

    if(!tmrpcm.isPlaying()){    //If no audio is playing, do something!
        stationsCLASS[selectedStationIndex]->play();
    }
}

void changeStation(bool up){
    stationsCLASS[selectedStationIndex]->stop();
    
    if(up){
        selectedStationIndex = (selectedStationIndex >= NUMBER_OF_STATIONS - 1) ? 0 : selectedStationIndex + 1;
    } else {
        selectedStationIndex = (selectedStationIndex <= 0) ? NUMBER_OF_STATIONS - 1 : selectedStationIndex - 1;
    }
    
    stationsCLASS[selectedStationIndex]->play();
}

void changeVolume(bool up){
    if(up){
        if(volumeG < maxVolume){
            volumeG++;
        }
    } else {
        if(volumeG > 0){
            volumeG--;
        }
    }
    tmrpcm.setVolume(volumeG);
}