/*
Simple 0 to 9 counter with 7 segment display!
https://www.clevertronics.blogspot.com
Used Hardware : Arduino UNO
Used IDE : Arduino IDE 1.8.12
*/

#include "SevSeg.h"
SevSeg sevseg; 

void setup()
{
    byte numDigits = 1;
    byte digitPins[] = {};
    byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
    bool resistorsOnSegments = true;

    byte hardwareConfig = COMMON_ANODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}

void loop()
{
    for(int i = 0; i < 10; i++){
        sevseg.setNumber(9);
        delay(1000);
        sevseg.refreshDisplay(); 
        }
}
