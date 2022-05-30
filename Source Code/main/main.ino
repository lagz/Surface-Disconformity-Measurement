//Author: Maxwell LaGassa\\

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "VL53L1X.h"

VL53L1X Distance_Sensor;

File myFile;
String filename = "Data-";
String filepath = "DATASETS/";
const int BUTTON_PIN = 2;
const int RED_LED_PIN = 7; 
const int GREEN_LED_PIN = 6;
const int ddelay = 50;
int currentState = LOW;
byte lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
int isRecording = 0;
int startFile = 0;
int filemod = 0;

void setup() 
{

    //Inputs and Outputs\\
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  //SD Card Setup\\
 
  if(!SD.begin(10))
  {
    failure();
  }
  SD.mkdir("DATASETS");
  filemod = createFileMod(filemod);
  
  //Distance Sensor Setup\\
  Wire.begin();
  Wire.setClock(400000);
  Distance_Sensor.setTimeout(500);
  if(!Distance_Sensor.init())
  {
    failure();
  }
  Distance_Sensor.setDistanceMode(VL53L1X::Short);
  Distance_Sensor.setMeasurementTimingBudget(50000);
  Distance_Sensor.startContinuous(50);

   //Set Red Light
  digitalWrite(7, HIGH);
}

void loop() 
{
  if(startFile == 1)
  {
    filemod = filemod + 1; 
    myFile = SD.open("DATASETS/" + filename + String(filemod) + ".txt", FILE_WRITE);
    startFile = 0;
  }
  if(isRecording == 1)
  {
    Distance_Sensor.read(); 
    myFile.print(int(Distance_Sensor.ranging_data.range_mm));
    myFile.print(',');
  }
  if(millis() - lastDebounceTime > ddelay)
  {
      byte buttonState = digitalRead(BUTTON_PIN);
      if(buttonState != lastButtonState)
      {
        lastDebounceTime = millis();
        lastButtonState = buttonState;
        if(buttonState == LOW)
        {
          if(isRecording == 0)
          {
            digitalWrite(RED_LED_PIN, LOW);
            digitalWrite(GREEN_LED_PIN, HIGH);
            isRecording = 1;
            startFile = 1;
          }
          else
          {
            digitalWrite(GREEN_LED_PIN, LOW);
            digitalWrite(RED_LED_PIN, HIGH);
            isRecording = 0;
            myFile.close();
          }
        }
      }
  }
  
}

//Failed to initialize MicroSD Card\\
void failure()
{
  while(1)
  {
      digitalWrite(7, HIGH);
      delay(200);
      digitalWrite(7, LOW);
      delay(200);
  }
}

//Create unique filenames for each dataset\\
int createFileMod(int filemod)
{
  if(!SD.exists("DATASETS/DATA-1.txt"))
  {
     return filemod;
  }
  int booln = 1;
  while(booln)
  {
     if(SD.exists("DATASETS/DATA-" + String(filemod+1) + ".txt"))
     {
        filemod = filemod + 1;
     }
     else
     {
        booln = 0;
        return filemod;
     }
  }
}
