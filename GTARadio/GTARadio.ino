#include "src/Button/Button.h"
#include "src/Potentiometer/Potentiometer.h"
#include "src/ScreenController/ScreenController.h"
#include "src/StationController/StationController.h"
#include "src/Station/Station.h"

#include "src/StationAbstract/StationAbstract.h"
#include "src/StationSplit/StationSplit.h"
#include "src/StationUnsplit/StationUnsplit.h"
#include "src/StationTalkshow/StationTalkshow.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#define SD_ChipSelectPin 4

TMRpcm tmrpcm;

Potentiometer volumeController = Potentiometer(A0, 10);

/*
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"Classic Rock", (char*)"01_CROCK");
StationSplit NON_STOP_POP = StationSplit((char*)"Non Stop Pop", (char*)"02_POP");
StationSplit RADIO_LOS_SANTOS = StationSplit((char*)"Radio Los Santos", (char*)"03_HH_N");
StationSplit CHANNEL_X = StationSplit((char*)"Channel X", (char*)"04_PUNK");
StationTalkshow WCTR = StationTalkshow((char*)"West Coast Talk Radio", (char*)"05_T_01");
StationSplit REBEL_RADIO = StationSplit((char*)"Rebel Radio", (char*)"06_CUNT");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");
StationSplit CLASSIC_ROCK = StationSplit((char*)"", (char*)"");*/

//StationAbstract station = StationSplit((char*)"AA", (char*)"BB");
//AbstractStation station1 = StationSplit((char*)"AA", (char*)"BB");
//AbstractStation stations[] = {station1};
//StationController stationController = StationController(stations);

ScreenController screen = ScreenController(0x27,16,2);    //0x27 for 20x4, 0x3f for 16x2
Button buttonA = Button(2);
Button buttonB = Button(3);
Button buttonC = Button(7);
Button buttonD = Button(8);

void setup()
{
    Serial.begin(9600);
    
    screen.setup();

    buttonA.setup();
    buttonB.setup();
    buttonC.setup();
    buttonD.setup();

    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
        return;   // don't do anything more if not
    }

    tmrpcm.speakerPin = 9;
    tmrpcm.volume(0.5);
    tmrpcm.play((char*)"CROATTSS.wav");
}

void loop()
{
    if(buttonA.stateChanged()){
        screen.setLine(0, "A");
        Serial.println("A");
    }
    if(buttonB.stateChanged()){
        screen.setLine(0, "B");
        Serial.println("B");
    }
    if(buttonC.stateChanged()){
        screen.setLine(0, "C");
        Serial.println("C");
    }
    if(buttonD.stateChanged()){
        screen.setLine(0, "D");
        Serial.println("D");
    }

    if(volumeController.stateChanged()){
        int volume = volumeController.getState();
        screen.setLine(1, String(map(volume, 0, 1023, 0, 7)));
    }
}