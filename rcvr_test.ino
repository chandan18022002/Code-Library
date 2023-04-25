#include <Servo.h>

#define RCPin_CH1 2
#define RCPin_CH2 3
#define RCPin_CH3 18
#define RCPin_CH4 19


Servo CH1;
Servo CH2;
Servo CH3;
Servo CH4;


volatile long StartTime_CH1 = 0;
volatile long CurrentTime_CH1 = 0;
volatile long Pulses_CH1 = 0;
int PulseWidth_CH1 = 0;

volatile long StartTime_CH2 = 0;
volatile long CurrentTime_CH2 = 0;
volatile long Pulses_CH2 = 0;
int PulseWidth_CH2 = 0;

volatile long StartTime_CH3 = 0;
volatile long CurrentTime_CH3 = 0;
volatile long Pulses_CH3 = 0;
int PulseWidth_CH3 = 0;

volatile long StartTime_CH4 = 0;
volatile long CurrentTime_CH4 = 0;
volatile long Pulses_CH4 = 0;
int PulseWidth_CH4 = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(RCPin_CH1, INPUT_PULLUP);
  pinMode(RCPin_CH2, INPUT_PULLUP);
  pinMode(RCPin_CH3, INPUT_PULLUP);
  pinMode(RCPin_CH4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(RCPin_CH1),PulseTimer_CH1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH2),PulseTimer_CH2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH3),PulseTimer_CH3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH4),PulseTimer_CH4,CHANGE);

  CH1.attach(12);
  CH2.attach(11);
  CH3.attach(10);
  CH4.attach(9);
  
  CH1.write(1000);
  CH2.write(1000);
  CH3.write(1000);
  CH4.write(1000);
}


void PulseTimer_CH1(){
  CurrentTime_CH1 = micros();
  if (CurrentTime_CH1 > StartTime_CH1){
    Pulses_CH1 = CurrentTime_CH1 - StartTime_CH1;
    StartTime_CH1 = CurrentTime_CH1;
  }
}
void PulseTimer_CH2(){
  CurrentTime_CH2 = micros();
  if (CurrentTime_CH2 > StartTime_CH2){
    Pulses_CH2 = CurrentTime_CH2 - StartTime_CH2;
    StartTime_CH2 = CurrentTime_CH2;
  }
}
void PulseTimer_CH3(){
  CurrentTime_CH3 = micros();
  if (CurrentTime_CH3 > StartTime_CH3){
    Pulses_CH3 = CurrentTime_CH3 - StartTime_CH3;
    StartTime_CH3 = CurrentTime_CH3;
  }
}
void PulseTimer_CH4(){
  CurrentTime_CH4 = micros();
  if (CurrentTime_CH4 > StartTime_CH4){
    Pulses_CH4 = CurrentTime_CH4 - StartTime_CH4;
    StartTime_CH4 = CurrentTime_CH4;
  }
}


void loop() {
  if (Pulses_CH1 < 2000){
    PulseWidth_CH1 = Pulses_CH1;
    CH1.write(PulseWidth_CH1);
  } 
  if (Pulses_CH2 < 2000){
    PulseWidth_CH2 = Pulses_CH2;
    CH2.write(PulseWidth_CH2);
  }
  if (Pulses_CH3 < 2000){
    PulseWidth_CH3 = Pulses_CH3;
    CH3.write(PulseWidth_CH3);
  } 
  if (Pulses_CH4 < 2000){
    PulseWidth_CH4 = Pulses_CH4;
    CH4.write(PulseWidth_CH4);
  } 
  Serial.print(PulseWidth_CH1);
  Serial.print(" , ");
  Serial.print(PulseWidth_CH2);
  Serial.print(" , ");
  Serial.print(PulseWidth_CH3);
  Serial.print(" , ");
  Serial.println(PulseWidth_CH4);
  
}
