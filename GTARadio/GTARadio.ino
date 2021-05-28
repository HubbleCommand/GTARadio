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
//StationAbstract station = StationSplit((char*)"AA", (char*)"BB");

Potentiometer volumeController = Potentiometer(A2, 10);

//AbstractStation station1 = StationSplit((char*)"AA", (char*)"BB");
//AbstractStation stations[] = {station1};
//StationController stationController = StationController(stations);

//ScreenController screen = ScreenController(0x3f,16,2);
ScreenController screen = ScreenController(0x3f,16,2);
Button buttonA = Button(2);
Button buttonB = Button(3);
Button buttonC = Button(7);
Button buttonD = Button(8);

String text2[2];

bool sdGood = true;

void setup()
{
    Serial.begin(9600);
    
    screen.setup();

    text2[0] = ("Hello, world!");
    text2[1] = ("Arduino!");

    buttonA.setup();
    buttonB.setup();
    buttonC.setup();
    buttonD.setup();

    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
        sdGood = false;
        return;   // don't do anything more if not
    }

    tmrpcm.speakerPin = 9;
    tmrpcm.volume(0.5);
    tmrpcm.play((char*)"WAV2/WAV/WAV/WAV/WAV/1.wav");
}
int counter = 0;
void loop()
{
    if(millis() % 10 == 0 && !sdGood){
        Serial.println("SD BAD");
    }

    if(buttonA.stateChanged()){
        text2[0] = "A";
        screen.setLine(0, "A");
        Serial.println("A");
    }
    if(buttonB.stateChanged()){
        text2[0] = "B";
        screen.setLine(0, "B");
        Serial.println("B");
    }
    if(buttonC.stateChanged()){
        text2[0] = "C";
        screen.setLine(0, "C");
        Serial.println("C");
    }
    if(buttonD.stateChanged()){
        text2[0] = "D";
        screen.setLine(0, "D");
        Serial.println("D");
    }

    if(volumeController.stateChanged()){
        int volume = volumeController.getState();
        text2[1] = String(volume);
    }

    counter++;
    if(counter == 10000){
        screen.update();
        counter = 0;
    }
}