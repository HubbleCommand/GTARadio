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
#define SD_ChipSelectPin 4

#if ((defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)))
    #define TMRPCM_SPEAKER_PIN 11   //Use pin 11 on the MEGA
#else
    #define TMRPCM_SPEAKER_PIN 9    //Use pin 9  on the UNO
#endif

#define NUMBER_OF_STATIONS 39
#define LCD_INTRO_LINE 0
#define LCD_CHANNEL_LINE 1
#define LCD_SONG_LINE 2
#define LCD_VOL_LINE 3

//This is really only intended to be used with a Mega, as TMRpcm requires lots of space when dealing with high sample rate audio

TMRpcm tmrpcm;
ScreenController screen = ScreenController(0x27,20,4);    //0x27 for 20x4, 0x3f for 16x2
Button butNextStation = Button(2);
Button butPrevStation = Button(3);
Button butNextSong = Button(40);
Button butPrevSong = Button(41);

StationAbstract* stationsCLASS[NUMBER_OF_STATIONS]; //Needs to be array of pointers, as is Abstract class (would otherwise need to import std::vector)

int selectedStationIndex;
int lastPotState;
int startTime = 0;

//GTA V Stations
StationSplit CLASSIC_ROCK = StationSplit((char*)"Los Santos Rock Radio", (char*)"01_CROCK", &tmrpcm, &screen);
StationSplit NON_STOP_POP = StationSplit((char*)"Non Stop Pop", (char*)"02_POP", &tmrpcm, &screen);
StationSplit RADIO_LOS_SANTOS = StationSplit((char*)"Radio Los Santos", (char*)"03_HH_N", &tmrpcm, &screen);
StationSplit CHANNEL_X = StationSplit((char*)"Channel X", (char*)"04_PUNK", &tmrpcm, &screen);
StationTalkshow WCTR = StationTalkshow((char*)"West Coast Talk Radio", (char*)"05_T1", &tmrpcm, &screen);
StationSplit REBEL_RADIO = StationSplit((char*)"Rebel Radio", (char*)"06_CUNT", &tmrpcm, &screen);
StationUnsplit SOULWAX = StationUnsplit((char*)"Soulwax FM", (char*)"07_DAN1", &tmrpcm, &screen);
StationUnsplit ELS = StationUnsplit((char*)"East Los FM", (char*)"08_MEX", &tmrpcm, &screen);
StationSplit WCC = StationSplit((char*)"West Coast Classics", (char*)"09_HH_O", &tmrpcm, &screen);
StationTalkshow BLAINE_CR = StationTalkshow((char*)"Blaine County Radio", (char*)"11_T2", &tmrpcm, &screen);
StationSplit BLUE_ARK = StationSplit((char*)"Blue Ark FM", (char*)"12_REGG", &tmrpcm, &screen);
StationUnsplit WORLDWIDE = StationUnsplit((char*)"WorldWide FM", (char*)"13_JAZZ", &tmrpcm, &screen);
StationUnsplit FLY_LO = StationUnsplit((char*)"FlyLo FM", (char*)"14_DAN2", &tmrpcm, &screen);
StationSplit LOW_DOWN = StationSplit((char*)"Low Down", (char*)"15_MTWN", &tmrpcm, &screen);
StationSplit MIRROR_PARK = StationSplit((char*)"Radio Mirror Park", (char*)"16_SILK", &tmrpcm, &screen);
StationSplit SPACE = StationSplit((char*)"Space", (char*)"17_FUNK", &tmrpcm, &screen);
StationSplit VB_RADIO = StationSplit((char*)"Vinewood Boulevard Radio", (char*)"18_90RK", &tmrpcm, &screen);

//GTA IV Stations
StationSplit IF_99 = StationSplit((char*)"International Funk 99", (char*)"A_AFRO", &tmrpcm, &screen);
StationSplit TUFF_GONG = StationSplit((char*)"Tuff Gong Radio", (char*)"B_BBYLN", &tmrpcm, &screen);
StationUnsplit THE_BEAT = StationUnsplit((char*)"The Beat 102.7", (char*)"C_BEAT", &tmrpcm, &screen);
StationUnsplit MASSIVE_B = StationUnsplit((char*)"Massive B Soundsystem 96.9", (char*)"D_BK", &tmrpcm, &screen);
StationSplit JOURNEY = StationSplit((char*)"The Journey", (char*)"E_CLASS", &tmrpcm, &screen);
StationUnsplit ELECTRO_CHOC = StationUnsplit((char*)"Electro-Choc", (char*)"F_DANM", &tmrpcm, &screen);
StationSplit RADIO_BROCKER = StationSplit((char*)"Radio Brocker", (char*)"G_DANR", &tmrpcm, &screen);
//WTF 8? Just extra songs?
StationSplit FUSION_FM = StationSplit((char*)"Fusion FM", (char*)"H_FUS", &tmrpcm, &screen);    //Not working?
StationSplit LC_HARD_CORE = StationSplit((char*)"Liberty City Hard Core", (char*)"I_HARD", &tmrpcm, &screen);
//!!! CHANNEL 11 WAS MEANT FOR A USER-MADE RADIO STATION ON PC VERSIONS OF GTA IV !!!
StationSplit JAZZ_NATION = StationSplit((char*)"Jazz Nation Radio 108.5", (char*)"J_JAZZ", &tmrpcm, &screen);
StationSplit K109 = StationSplit((char*)"K109 The Studio", (char*)"K_K109", &tmrpcm, &screen);
StationTalkshow INTEGRITY = StationTalkshow((char*)"Integrity 2.0", (char*)"L_LZLW", &tmrpcm, &screen);
StationSplit LIBERTY_ROCK = StationSplit((char*)"Liberty Rock Radio", (char*)"M_LIBR", &tmrpcm, &screen);
StationSplit ACTUALIZATION = StationSplit((char*)"Self-Actualization FM", (char*)"N_MED", &tmrpcm, &screen);
StationUnsplit THE_CLASSICS = StationUnsplit((char*)"The Classics 104.1", (char*)"O_NYCL", &tmrpcm, &screen); //Not sure about name...
StationTalkshow PLR = StationTalkshow((char*)"Public Liberty Radio", (char*)"P_PLR", &tmrpcm, &screen);
StationUnsplit RAMJAM = StationUnsplit((char*)"RamJam FM", (char*)"Q_RJFM", &tmrpcm, &screen);
StationSplit SAN_JUAN_SOUNDS = StationSplit((char*)"San Juan Sounds", (char*)"R_SJS", &tmrpcm, &screen);
StationSplit THE_VIBE = StationSplit((char*)"The Vibe 98.8", (char*)"S_VIBE", &tmrpcm, &screen);
StationSplit VCFM = StationSplit((char*)"Vice City FM", (char*)"T_VCFM", &tmrpcm, &screen);
StationSplit VLADIVOSTOK = StationSplit((char*)"Vladivostok FM", (char*)"U_VLAD", &tmrpcm, &screen);
StationTalkshow WKTT = StationTalkshow((char*)"WKTT Radio", (char*)"V_WKTT", &tmrpcm, &screen);

void setup()
{
    randomSeed(analogRead(A0) / analogRead(A1) + 1);

    screen.setup();
    butNextStation.setup();
    butPrevStation.setup();

    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
        screen.setLine(0, "SD ISSUE");
        return;   // don't do anything more if not
    } else {
        screen.setLine(0, "GTA Radio");
    }

    tmrpcm.speakerPin = TMRPCM_SPEAKER_PIN;
    tmrpcm.volume(0.5);
    //tmrpcm.quality(1);
    selectedStationIndex = random(NUMBER_OF_STATIONS);   //DON't -1 ! the max is EXCLUSIVE
    
    stationsCLASS[0] = &CLASSIC_ROCK;
    stationsCLASS[1] = &NON_STOP_POP;
    stationsCLASS[2] = &RADIO_LOS_SANTOS;
    stationsCLASS[3] = &CHANNEL_X;
    stationsCLASS[4] = &WCTR;
    stationsCLASS[5] = &REBEL_RADIO;
    stationsCLASS[6] = &SOULWAX;
    stationsCLASS[7] = &ELS;
    stationsCLASS[8] = &WCC;
    stationsCLASS[9] = &BLAINE_CR;
    stationsCLASS[10] = &BLUE_ARK;
    stationsCLASS[11] = &WORLDWIDE;
    stationsCLASS[12] = &FLY_LO;
    stationsCLASS[13] = &LOW_DOWN;
    stationsCLASS[14] = &MIRROR_PARK;
    stationsCLASS[15] = &SPACE;
    stationsCLASS[16] = &VB_RADIO;
    stationsCLASS[17] = &IF_99;
    stationsCLASS[18] = &TUFF_GONG;
    stationsCLASS[19] = &THE_BEAT;
    stationsCLASS[20] = &MASSIVE_B;
    stationsCLASS[21] = &JOURNEY;
    stationsCLASS[22] = &ELECTRO_CHOC;
    stationsCLASS[23] = &RADIO_BROCKER;
    stationsCLASS[24] = &FUSION_FM;
    stationsCLASS[25] = &LC_HARD_CORE;
    stationsCLASS[26] = &JAZZ_NATION;
    stationsCLASS[27] = &K109;
    stationsCLASS[28] = &INTEGRITY;
    stationsCLASS[29] = &LIBERTY_ROCK;
    stationsCLASS[30] = &ACTUALIZATION;
    stationsCLASS[31] = &THE_CLASSICS;
    stationsCLASS[32] = &PLR;
    stationsCLASS[33] = &RAMJAM;
    stationsCLASS[34] = &SAN_JUAN_SOUNDS;
    stationsCLASS[35] = &THE_VIBE;
    stationsCLASS[36] = &VCFM;
    stationsCLASS[37] = &VLADIVOSTOK;
    stationsCLASS[38] = &WKTT;

    //Not updating the screen pointer AFTER THE SCREEN HAS BEEN SETUP causes issues
    for(int i = 0; i < NUMBER_OF_STATIONS; i++){
        stationsCLASS[i]->screen = &screen;
    }

    selectedStationIndex = 0;
    stationsCLASS[selectedStationIndex]->play();
}

void loop()
{    
    if(butNextStation.stateChanged()){
        stationsCLASS[selectedStationIndex]->stop();

        if(selectedStationIndex >= NUMBER_OF_STATIONS - 1){
            selectedStationIndex = 0;
        } else {
            selectedStationIndex++;
        }
        
        stationsCLASS[selectedStationIndex]->play();
    }

    if(butPrevStation.stateChanged()){
        stationsCLASS[selectedStationIndex]->stop();
        
        if(selectedStationIndex <= 0){
            selectedStationIndex = NUMBER_OF_STATIONS - 1;
        } else {
            selectedStationIndex--;
        }

        stationsCLASS[selectedStationIndex]->play();
    }

    if(butNextSong.stateChanged()){     //TODO check if increasing button debounce time fixed the total crash if next / prev song is pushed too soon
        stationsCLASS[selectedStationIndex]->nextSong();
    }

    if(butPrevSong.stateChanged()){
        stationsCLASS[selectedStationIndex]->prevSong();
    }

    int reading = analogRead(A0);
    if(abs(reading - lastPotState) > 50){
        lastPotState = reading;
        int volume = map(reading, 0, 1023, 0, 7);
        tmrpcm.setVolume(volume);

        char tmpString[9];
        sprintf(tmpString, "VOL :  %i", volume);
        screen.setLine(LCD_VOL_LINE, tmpString);
    }

    if(!tmrpcm.isPlaying()){    //If no audio is playing, do something!
        stationsCLASS[selectedStationIndex]->play();
    }
}
