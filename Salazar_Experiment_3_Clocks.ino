#include "SevSeg.h"
SevSeg sevseg; 

unsigned long previousMillis = 0UL;
unsigned long interval = 1000UL;
int secTime = 0;
int firstMinTime = 0;
int secondMinTime = 0;
int firstHourTime = 2;
int secondHourTime = 1;
int hourTime = 0;
int displayTime= 0;
bool firstRotate = false;
uint8_t firstBit;
uint8_t secondBit;
uint8_t thirdBit;
uint8_t fourthBit;
int incSwitch = A5;
int decSwitch = A3;
int changeSwitch = A4;
bool inHour = false;

void setup()
{
  pinMode(incSwitch, INPUT_PULLUP);
  pinMode(decSwitch, INPUT_PULLUP);
  pinMode(changeSwitch, INPUT_PULLUP);
  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
	  for(int i; i < 60; i++){
    
    }
 	  previousMillis = currentMillis;
    secTime++;
    if (secTime == 60) {
      firstMinTime++;
      secTime = 0;
    }
    if (firstMinTime == 10) {
      secondMinTime++;
      firstMinTime = 0;
    }
    if (secondMinTime == 6) {
      firstHourTime++;
      secondMinTime = 0;
    }
    if (firstHourTime == 10 && firstRotate == false) {
      firstRotate = true;
      secondHourTime++;
      firstHourTime = 0;
    }
    if (firstHourTime < 2 && firstRotate == true) {
      firstRotate = false;
      secondHourTime = 0;
      firstHourTime = 1;
    }
    
  }

  if (digitalRead(changeSwitch) == LOW) {
      inHour = !inHour;
  }
  if (digitalRead(decSwitch) == LOW) {
      if (inHour == false) {
        if (firstMinTime == 10) {
          firstMinTime = 0;
          secondMinTime++;
        }
        else {
          firstMinTime++;
        }
      }
      else {
      if (firstHourTime == 10) {
        firstHourTime = 0;
        secondHourTime++;
        firstRotate = true;
      }
      else {
        firstHourTime++;
      }
    }
  }
  if (digitalRead(incSwitch) == LOW) {
    if (inHour == false) {
      if (firstMinTime == 0) {
        firstMinTime = 9;
        if(secondMinTime == 0) {
          secondMinTime = 5;
          if (firstHourTime == 0) {
            firstHourTime = 9;
            secondHourTime = 0;
          }
          else if (firstHourTime == 1) {
            firstHourTime = 2;
            secondHourTime = 1;
          }
          else {
            firstHourTime--;
          }
        }
        else {
          secondMinTime--;
        }  
      }
      else {
        firstMinTime--;
      }
    }
    else {
      if (firstHourTime == 0) {
            firstHourTime = 9;
            secondHourTime = 0;
          }
          else if (firstHourTime == 1) {
            firstHourTime = 2;
            secondHourTime = 1;
          }
    }
  }
  
  switch(firstMinTime) {
    case 0:
    firstBit = 0b00111111;
    break;
    case 1:
    firstBit = 0b00000110;
    break;
    case 2:
    firstBit = 0b01011011;
    break;
    case 3:
    firstBit = 0b01001111;
    break;
    case 4:
    firstBit = 0b01100110;
    break;
    case 5:
    firstBit = 0b01101101;
    break;
    case 6:
    firstBit = 0b01111101;
    break;
    case 7:
    firstBit = 0b00000111;
    break;
    case 8:
    firstBit = 0b01111111;
    break;
    case 9:
    firstBit = 0b01101111;
    break;
  }

  switch(secondMinTime) {
    case 0:
    secondBit = 0b00111111;
    break;
    case 1:
    secondBit = 0b00000110;
    break;
    case 2:
    secondBit = 0b01011011;
    break;
    case 3:
    secondBit = 0b01001111;
    break;
    case 4:
    secondBit = 0b01100110;
    break;
    case 5:
    secondBit = 0b01101101;
    break;
    case 6:
    secondBit = 0b01111101;
    break;
    case 7:
    secondBit = 0b00000111;
    break;
    case 8:
    secondBit = 0b01111111;
    break;
    case 9:
    secondBit = 0b01101111;
    break;
  }

  switch(firstHourTime) {
    case 0:
    secondBit = 0b10111111;
    break;
    case 1:
    thirdBit = 0b10000110;
    break;
    case 2:
    thirdBit = 0b11011011;
    break;
    case 3:
    thirdBit = 0b11001111;
    break;
    case 4:
    thirdBit = 0b11100110;
    break;
    case 5:
    thirdBit = 0b11101101;
    break;
    case 6:
    thirdBit = 0b11111101;
    break;
    case 7:
    thirdBit = 0b10000111;
    break;
    case 8:
    thirdBit = 0b11111111;
    break;
    case 9:
    thirdBit = 0b11101111;
    break;
  }
  
  switch(secondHourTime) {
    case 0:
    fourthBit = 0b00111111; 
    break;
    case 1:
    fourthBit = 0b00000110;
  }
  
  sevseg.setSegmentsDigit(3, firstBit);
  sevseg.setSegmentsDigit(2, secondBit);
  sevseg.setSegmentsDigit(1, thirdBit);
  sevseg.setSegmentsDigit(0, fourthBit);
  sevseg.refreshDisplay();
  
}