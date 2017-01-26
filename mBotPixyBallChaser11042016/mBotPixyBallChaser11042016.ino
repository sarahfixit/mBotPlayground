
//#include <MeRGBLed.h>
//#include <MeBluetooth.h>

#include <RBD_Timer.h> //Useful Time functions
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Pixy.h> //Pixy factory header

#include "mBot.h" //Makeblock factory header: watch dependency chain if you change this
//#include "MePort.h" //Makeblock factory port mapping
#include "MeDCMotor.h" //Makeblock factory DC motor control 
//#include <MeMCore.h>

//Make instances of objects
MeBoard myBoard(mBot);
Pixy pixy;
RBD::Timer turnAroundTimer(200);


//Variables: Object Detection
int signature = 1;

int x = 0;
int y = 0;
unsigned int width = 0;
unsigned int height = 0;
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 100;
int Xmax = 200;
int maxArea = 10000;
int maxAvoidanceArea = 10000;
int minArea = 2000;
static int i = 0;



// demoProgram timer variables
unsigned long demoSignatureChangeInterval = 20000; //20 sec
unsigned long demoSignatureChangeCounterPrevious = 0;
  unsigned long demoSignatureChangeCounterCurrent = 0;

  
int declaredSignature = 3;
String incomingSignature = "Yellow";

//Variables: motors

int motorSpeed = 150;  // <--------------MOTOR SPEED-----<---------<-----
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);


void setup(){
    Stop(); //motor.Stop();
    Serial.begin(9600);
    pixy.init();
}

void loop(){
    while (millis() < 3000)
    {
     scan();
     area = width * height;
    }

scan();

//serialOutput(); //pixyCam output
    
      incomingSignature = Serial.read();

       if (incomingSignature)
       {
            if (incomingSignature = 'Blue')
            {
              declaredSignature == 1;
              //Serial.println("Blue received.");
              //onBoardLED.setColor(0,0,0,255);
              //onBoardLED.show();
            }
            else if(incomingSignature = 'Red')
            {
              declaredSignature == 2;
              // Serial.println("Red received.");
              //onBoardLED.setColor(0,255,0,0);
              //onBoardLED.show();
            }
            else if (incomingSignature = 'Yellow')
            {
              declaredSignature == 3;
              // Serial.println("Yellow received.");
              //onBoardLED.setColor(0,255,150,0);
              //onBoardLED.show();
            }
            else if (incomingSignature = 'Green')
            {
              declaredSignature == 4;
              // Serial.println("Green received.");
              //onBoardLED.setColor(0,0,255,0);
              //onBoardLED.show();
            }
            else 
            {
              //
            } 
        }
        else
        {
          //demo in case of no serial data
          demoProgram();
        }

    newarea = width * height;
    
    if (signature > 4 && newarea > maxAvoidanceArea)
            {
              backward();
              turnAroundTimer.restart();
              while (turnAroundTimer.isActive())
              {
               aboutFace();
              }
            }
     else if (newarea>maxArea)
     {
      backward;
     }
     
    if (signature = declaredSignature )
     {
       
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
}

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
void aboutFace()
{
  motor_9.run((9) == M1 ? -(-motorSpeed) : (-motorSpeed));
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
}//close Serial 

void demoProgram()
{ 
      demoSignatureChangeCounterCurrent = millis();

         if((demoSignatureChangeCounterCurrent)-(demoSignatureChangeCounterPrevious)>= (demoSignatureChangeInterval) )
           {
             demoSignatureChangeCounterPrevious = demoSignatureChangeCounterCurrent; //save the last time we changed declaredSignature

             if(declaredSignature>3)
             {declaredSignature = 1;}
             else
             {declaredSignature++;}
           }
}
