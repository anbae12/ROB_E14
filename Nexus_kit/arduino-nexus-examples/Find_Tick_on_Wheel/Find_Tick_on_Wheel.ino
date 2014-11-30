/*****************************************************************************
 * Bachelor Project:
 * Controlling mobile robot with online mapping and planning
 * Authors:
 * Tim Larsen and Michel Rabjerg
 * Robot technology
 * University of Southern Denmark
 *****************************************************************************
 * For:     Arduino
 * Test of motors using Bumpers for controle
 *
 *****************************************************************************/

#include <PinChangeInt.h> 
#include <PinChangeIntConfig.h>
/*********************************************/
// Definements
#define changeDir(x) if(x==1){digitalWrite(pinWheelRightDIR,LOW);digitalWrite(pinWheelLeftDIR,HIGH);}else if(x==2){digitalWrite(pinWheelRightDIR,HIGH);digitalWrite(pinWheelLeftDIR,LOW);}

#define SPEED_IN_TURNS 75
#define NUMBER_OF_PULSES_IN_TURN 12
/*********************************************/
// test var
int ticks = 0;
int stopTickAt = 12;
int level = 0;
/*********************************************/
// LED
int pinLed = 13;
/*********************************************/
// Bumper
unsigned char pinBumperLeft    = 12;
unsigned char pinBumperCenter  = 3;
unsigned char pinBumperRight   = 2;
/*********************************************/
// Motor
// - Pins
unsigned char pinWheelRightPWM    = 10;
unsigned char pinWheelRightDIR    = 11;
unsigned char pinWheelRightIRQ    = 6;
unsigned char pinWheelRightIRQB   = 7;

unsigned char pinWheelLeftPWM     = 9;
unsigned char pinWheelLeftDIR     = 8;
unsigned char pinWheelLeftIRQ     = 4;
unsigned char pinWheelLeftIRQB    = 5;

// - vars
int tick = 0;


/*********************************************/

void setup() 
{
  //setup of timer used for PWM on pin 9, 10
  TCCR1B = TCCR1B&0xf8|0x01;
  
  //setup pinmode for led
  pinMode(pinLed,OUTPUT);  
  
  //setup of pins for wheel
  pinMode(pinWheelRightPWM,OUTPUT);
  pinMode(pinWheelRightDIR,OUTPUT);

  pinMode(pinWheelLeftPWM,OUTPUT);
  pinMode(pinWheelLeftDIR,OUTPUT);
  
  //setup pinmode for interrupts 
  pinMode(pinWheelRightIRQ,INPUT);
  pinMode(pinWheelRightIRQB,INPUT);
  pinMode(pinWheelLeftIRQ,INPUT);
  pinMode(pinWheelLeftIRQB,INPUT);
  
  //attach interrupts tothe pins
  PCattachInterrupt(pinWheelRightIRQ,interrupt,HIGH);

  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void interrupt()
{
  tick += 1;

}


void loop() 
{
    Serial.print(tick);
    Serial.print("\n");
 
  delay(300);
}


