//SJW: Look at using "RBD Timer" for timing functions


#include <MeUltrasonicSensor.h>
#include <NewPing.h>

#include <Arduino.h>
#include <SPI.h>
#include <Pixy.h>
#include <SoftwareSerial.h>
#include "mBot.h"
#include "MePort.h"
#include "MeDCMotor.h"


#define TRIGGER_PIN  A4
#define ECHO_PIN     A4
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters)


//Make instances of objects
MeBoard myBoard(mBot);
Pixy pixy;
MeUltrasonicSensor ultrasonic_3(3);
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//variables
//Object sensing variables
int signature = 1;

int x = 0;
int y = 0;
unsigned int width = 0;
unsigned int height = 0;
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 100;
int Xmax = 200;
int maxArea = 4000;
int minArea = 2500;
static int i = 0; //pixy array subscript

//For wall avoidance movement
const long INTERVAL = 500;
unsigned long avoidanceStartTime = 0;
unsigned long avoidanceStopBackupTime = 0;
unsigned long avoidanceStopTurnRightTime = 0;
//for demo signature changes
unsigned long signatureChangeInterval = 20000; //20 sec
unsigned long signatureChangeCounterPrevious = 0;
unsigned long signatureChangeCounterCurrent = 0;
int declaredSignature = 1;
int chasingSignature = 1;

int motorSpeed = 150;
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);



void setup()
{
  Stop();
  pixy.init();


  //optional serial output of ping distance
  Serial.begin(9600);
  Serial.print("Starting...\n");

  //set baud rate for Pixy Serial output
  //Serial.begin(9600);

  avoidanceStartTime = millis();
  //set state timers to mirror start time (manipulating working interval)
  avoidanceStopBackupTime = avoidanceStartTime;
  avoidanceStopTurnRightTime = avoidanceStartTime + INTERVAL;
}

void loop()
{

  //Serial output for testing PixyCam
  //serialOutput();

  //Serial output for Ping Sensor
  //Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  //Serial.println("cm");

  //on boot, scan for X seconds to identify objects
  //(will likely need to be adjusted)
  
      while (millis() < 1000)
    {
     scan();
     area = width * height;
     //maxArea = area + 500;
     //minArea = area - 1000;
    }



/*
    //if >5cm from obstacle, back the truck up
    if ((sonar.ping_cm() > 0) && (sonar.ping_cm() < 5 ))
    {
     avoidanceStartTime = millis();

     if ((avoidanceStartTime - avoidanceStopBackupTime) < INTERVAL)
     {
       backward();
     }
     else if ((avoidanceStartTime - avoidanceStopTurnRightTime) < INTERVAL)
     {
       right();
     }
     else
     {
       Stop();
       avoidanceStopBackupTime = avoidanceStartTime;
       avoidanceStopTurnRightTime = avoidanceStartTime + INTERVAL;
     }



    }
    */

    //else scan for object signatures (set in PixyMon application)
//    else
    {
     //if (Serial.available() > 0)
       //{
        // declaredSignature = Serial.read();
       //}
     //else
     //this is test/demo code. signature will change every X milliseconds
       {
 //this is test/demo code. signature will change every X milliseconds
         signatureChangeCounterCurrent = millis();

         if((signatureChangeCounterCurrent)-(signatureChangeCounterPrevious)>= (signatureChangeInterval) )
           {
             signatureChangeCounterPrevious = signatureChangeCounterCurrent; //save the last time we changed declaredSignature

             if(declaredSignature>3)
             {declaredSignature = 1;}
             else
             {declaredSignature++;}
           }

       }
     scan();
     signature = declaredSignature;
     /*
  if (signature = declaredSignature )
     {


       newarea = width * height;

       if (x < Xmin)
       {
         left();
       }
       else if (x > Xmax)
       {
         right();
       }
       else if (newarea < minArea)
       {
         forward();
       }
       else if (newarea > maxArea)
       {
         backward();
       }

     }
     else 
     {
      Stop();
      scan();
     }
     */

     //built for up to 4 signatures (we bought 4 buttons)
     if (signature == 1 )
     {


       newarea = width * height;

       if (x < Xmin)
       {
         left();
       }
       else if (x > Xmax)
       {
         right();
       }
       else if (newarea < minArea)
       {
         forward();
       }
       else if (newarea > maxArea)
       {
         backward();
       }

     }
     else if  (signature == 2)
     {


       newarea = width * height;

       if (x < Xmin)
       {
         left();
       }
       else if (x > Xmax)
       {
         right();
       }
       else if (newarea < minArea)
       {
         forward();
       }
       else if (newarea > maxArea)
       {
         backward();
       }

     }
     else if  (signature == 3)
     {


       newarea = width * height;

       if (x < Xmin)
       {
         left();
       }
       else if (x > Xmax)
       {
         right();
       }
       else if (newarea < minArea)
       {
         forward();
       }
       else if (newarea > maxArea)
       {
         backward();
       }

     }
     else if  (signature == 4)
     {


       newarea = width * height;

       if (x < Xmin)
       {
         left();
       }
       else if (x > Xmax)
       {
         right();
       }
       else if (newarea < minArea)
       {
         forward();
       }
       else if (newarea > maxArea)
       {
         backward();
       }

     }
      else
     {
       Stop();
     }
    }
  
    
} //close loop




void backward()
{
  motor_9.run((9) == M1 ? -(-motorSpeed) : (-motorSpeed));
  motor_10.run((10) == M1 ? -(-motorSpeed) : (-motorSpeed));
}

void forward()
{
  motor_9.run((9) == M1 ? -(motorSpeed) : (motorSpeed));
  motor_10.run((10) == M1 ? -(motorSpeed) : (motorSpeed));
}

void right()
{
  motor_9.run((9) == M1 ? -(motorSpeed) : (motorSpeed));
  motor_10.run((10) == M1 ? -(0) : (0));
}

void left()
{
  motor_9.run((9) == M1 ? -(0) : (0));
  motor_10.run((10) == M1 ? -(motorSpeed) : (motorSpeed));
}

void Stop()
{
  motor_9.run((9) == M1 ? -(0) : (0));
  motor_10.run((10) == M1 ? -(0) : (0));
}

void scan()
{
  uint16_t blocks;
  blocks = pixy.getBlocks();
  signature = pixy.blocks[i].signature;

  x = pixy.blocks[i].x;
  y = pixy.blocks[i].y;
  width = pixy.blocks[i].width;
  height = pixy.blocks[i].height;
}

void serialOutput()
{
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];

  // grab blocks!
  blocks = pixy.getBlocks();

  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;

    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i % 50 == 0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j = 0; j < blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();
      }
    }
  }
}//close Serial Output



