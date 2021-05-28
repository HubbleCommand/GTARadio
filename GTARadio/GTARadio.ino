#include "src/Button/Button.h"
#include "src/Potentiometer/Potentiometer.h"
#include "src/ScreenController/ScreenController.h"
#include "src/StationController/StationController.h"
#include "src/Station/Station.h"

#include "src/StationAbstract/StationAbstract.h"
#include "src/StationSplit/StationSplit.h"
#include "src/StationUnsplit/StationUnsplit.h"

#include <TMRpcm.h>
#define SD_ChipSelectPin 4

TMRpcm tmrpcm;

Potentiometer volumeController = Potentiometer(A2, 10);

//StationAbstract station = StationSplit((char*)"AA", (char*)"BB");
//AbstractStation station1 = StationSplit((char*)"AA", (char*)"BB");
//AbstractStation stations[] = {station1};
//StationController stationController = StationController(stations);

//ScreenController screen = ScreenController(0x3f,16,2);
ScreenController screen = ScreenController(0x3f,16,2);
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
    tmrpcm.play((char*)"WAV2/WAV/WAV/WAV/WAV/1.wav");
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
        screen.setLine(1, String(volume));
    }
}