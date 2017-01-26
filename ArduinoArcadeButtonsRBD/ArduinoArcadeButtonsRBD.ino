#include <RBD_Button.h> 
#include <RBD_Timer.h>


//Button object instances
// INPUT_PULLUP Disabled Warning: this example requires resistors in your circuit
RBD::Button BlueButton(2, false); //Blue button on pin2, pull_up flag
RBD::Button RedButton(4, false); //Red button on 2, pull_up flag
RBD::Button YellowButton(6, false); //Yellow button on 6, pull_up flag
RBD::Button GreenButton(8, false); //Green button on 8, pull_up flag

//Timer object instances
RBD::Timer SleepTimer; //
RBD::Timer SleepProgramTimer;

void setup() {
 //initialize bluetooth as serial output
  Serial.begin(9600);
  Serial.println("Starting...");

  //start Sleep timers
  SleepTimer.setTimeout(300000); //5 min = 300K
  SleepTimer.restart();
  SleepProgramTimer.setTimeout(60000); //1min = 60K
  
}

void loop() {
  //Serial.println("Bluetooth test.");

  if(BlueButton.onPressed())
  {
    Serial.println("Blue");
    SleepTimer.restart();
  }
  if(RedButton.onPressed())
  {
    Serial.println("Red");
    SleepTimer.restart();
  }
  if(YellowButton.onPressed())
  {
    Serial.println("Yellow");
    SleepTimer.restart();
  }
  if(GreenButton.onPressed())
  {
    Serial.println("Green");
    SleepTimer.restart();
  }
  
  if (SleepTimer.isExpired())
    {
      SleepProgramTimer.restart();
    }
  

}
