#include <MotorWheel.h> 
#include <Omni3WD.h>
#include <Omni4WD.h>
#include <R2WD.h>
#include <PID_Beta6.h>
#include <PinChangeInt.h> 
#include <PinChangeIntConfig.h>
#include <SONAR.h> // Include the header files

boolean test = true;

irqISR(irq1,isr1); // Intterrupt function.on the basis of the pulse, work for wheel1
MotorWheel wheel1(9,8,4,5,&irq1,REDUCTION_RATIO,int(144*PI));
irqISR(irq2,isr2);
MotorWheel wheel2(10,11,6,7,&irq2,REDUCTION_RATIO,int(144*PI));
R2WD _2WD(&wheel1,&wheel2,WHEELSPAN);
unsigned int speedMMPS=160;

void setup() {
  TCCR1B=TCCR1B&0xf8|0x01;

  _2WD.PIDEnable(0.26,0.02,0,10); // Enable PID
  Serial.begin(9600);
    while (!Serial){;}
}

void loop() {

  if(test)
  {  
    _2WD.setCarAdvanceDistance(speedMMPS,4000);
    _2WD.setCarStop();
    test = false;
  } 
  
  _2WD.PIDRegulate(); // PID regulate the speed

}

