/*#include <MotorWheel.h> 
#include <Omni3WD.h>
#include <Omni4WD.h>
#include <R2WD.h>
#include <PID_Beta6.h>
#include <PinChangeInt.h> 
#include <PinChangeIntConfig.h>
#include <SONAR.h> // Include the header files

int robotStates = 0;
boolean test = true;

irqISR(irq1,isr1); // Intterrupt function.on the basis of the pulse, work for wheel1
MotorWheel wheel1(9,8,4,5,&irq1,REDUCTION_RATIO,int(144*PI));
irqISR(irq2,isr2);
MotorWheel wheel2(10,11,6,7,&irq2,REDUCTION_RATIO,int(144*PI));
R2WD _2WD(&wheel1,&wheel2,WHEELSPAN);

unsigned int speedStraight = 400;
unsigned int speedRotate = 110;

void setup() {
  TCCR1B=TCCR1B&0xf8|0x01;

  _2WD.PIDEnable(0.36,0.02,1,10); // Enable PID
  Serial.begin(9600);
    while (!Serial){;}
}

void loop() {
/*
  switch(robotStates){
    case 0:
       _2WD.setCarAdvanceDistance(speedStraight,200);
       _2WD.setCarStop();
       robotStates = ;
      break;
   case 1:
     _2WD.setCarRotateRightAngle(speedRotate,(0.5*PI));
     _2WD.setCarStop();
     robotStates = 2;
     break;
    case 2:
      _2WD.setCarAdvanceDistance(speedStraight,14);
      _2WD.setCarStop();
      robotStates = 3;
      break;
   case 3:
     _2WD.setCarRotateRightAngle(speedRotate,(0.5*PI));
     _2WD.setCarStop();
     robotStates = 4;
     break;
   case 4:
       _2WD.setCarAdvanceDistance(speedStraight,20);
       _2WD.setCarStop();
       robotStates = 5;
     break;
    case 5:
        _2WD.setCarStop();
      break;
    default
      break;
  }
 
  if(test)
  {  
    _2WD.setCarAdvanceDistance(speedMMPS,4000);
    _2WD.setCarStop();
    test = false;
  } 
  
  _2WD.PIDRegulate(); // PID regulate the speed

}


*/




String numInt;

const int led=13;
void setup() { 
 //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
}


int x=0;
void loop(){
  
  
  if(Serial.available() > 0){
        String str = Serial.readStringUntil(',');
        x = Serial.parseInt();
        Serial.println(str);
        Serial.println(x);
    }
  digitalWrite(led,HIGH);
  delay(x);
  digitalWrite(led,HIGH);
  
  
  
}


/*
void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if(incomingByte=='Led'){
    
    if(incomingByte=='H'){  
     digitalWrite(led, HIGH);
    }else
    digitalWrite(led, LOW);
    
    }
  }
}
   */   /*
      Serial.println("Change led state...");
        while (Serial.available() > 0) {;
          digitalWrite(led, HIGH);
	  char incoming = Serial.read();
          numInt += incoming;
          delay(2);
          int n = numInt.toInt();



          Serial.print("Led is set to high: ");
          Serial.print(n);
          Serial.println(" [ms].");
          delay(n);
          digitalWrite(led, LOW);
          Serial.write("Led is set to low\n");
    }
        
    }
  }
}
*/
/*
void loop() {
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string 
    int n = readString.toInt();  //convert readString into a number

    // auto select appropriate value, copied from someone elses code.
    if(n >= 500)
    {
      Serial.print("writing Microseconds: ");
      Serial.println(n);
      digitalWrite(led, LOW);
    }
    else
    {   
      Serial.print("writing Angle: ");
      Serial.println(n);
      myservo.write(n);
    }

    readString=""; //empty for next input
  } 
}*/
