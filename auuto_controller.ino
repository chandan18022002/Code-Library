#include <Servo.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(48,49); // CE, CSN

const byte address[6] = "00001";
short Array[6];

#define RCPin_CH1 2
#define RCPin_CH2 3
#define RCPin_CH3 18
#define RCPin_CH4 19
#define RCPin_CH5 20
#define RCPin_CH6 21


Servo CH1;
Servo CH2;
Servo CH3;
Servo CH4;
Servo CH5;
Servo CH6;


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

volatile long StartTime_CH5 = 0;
volatile long CurrentTime_CH5 = 0;
volatile long Pulses_CH5 = 0;
int PulseWidth_CH5 = 0;

volatile long StartTime_CH6 = 0;
volatile long CurrentTime_CH6 = 0;
volatile long Pulses_CH6 = 0;
int PulseWidth_CH6 = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  pinMode(RCPin_CH1, INPUT_PULLUP);
  pinMode(RCPin_CH2, INPUT_PULLUP);
  pinMode(RCPin_CH3, INPUT_PULLUP);
  pinMode(RCPin_CH4, INPUT_PULLUP);
  pinMode(RCPin_CH5, INPUT_PULLUP);
  pinMode(RCPin_CH6, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(RCPin_CH1),PulseTimer_CH1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH2),PulseTimer_CH2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH3),PulseTimer_CH3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH4),PulseTimer_CH4,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH5),PulseTimer_CH5,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPin_CH6),PulseTimer_CH6,CHANGE);

  
  CH1.attach(12);
  CH2.attach(11);
  CH3.attach(10);
  CH4.attach(9);
  CH5.attach(8);
  CH6.attach(7);
  
  CH1.write(1500);
  CH2.write(1500);
  CH3.write(1000);
  CH4.write(1500);
  CH5.write(1850);
  CH6.write(1000);
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
void PulseTimer_CH5(){
  CurrentTime_CH5 = micros();
  if (CurrentTime_CH5 > StartTime_CH5){
    Pulses_CH5 = CurrentTime_CH5 - StartTime_CH5;
    StartTime_CH5 = CurrentTime_CH5;
  }
}
void PulseTimer_CH6(){
  CurrentTime_CH6 = micros();
  if (CurrentTime_CH6 > StartTime_CH6){
    Pulses_CH6 = CurrentTime_CH6 - StartTime_CH6;
    StartTime_CH6 = CurrentTime_CH6;
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
  if (Pulses_CH5 < 2000){
    PulseWidth_CH5 = Pulses_CH5;
    PulseWidth_CH5+=20;
    CH5.write(PulseWidth_CH5);
  } 
  if (Pulses_CH6 < 2000){
    PulseWidth_CH6 = Pulses_CH6;
  } 
  Serial.print(PulseWidth_CH1);
  Serial.print(" , ");
  Serial.print(PulseWidth_CH2);
  Serial.print(" , ");
  Serial.print(PulseWidth_CH3);
  Serial.print(" , ");
  Serial.print(PulseWidth_CH4);
  Serial.print(" , ");
  Serial.print(PulseWidth_CH5);
  Serial.print(" , ");
  Serial.println(PulseWidth_CH6);/*

  Array[0]=PulseWidth_CH1;
  Array[1]=PulseWidth_CH2;
  Array[2]=PulseWidth_CH3;
  Array[3]=PulseWidth_CH4;
  Array[4]=PulseWidth_CH5;
  Array[5]=PulseWidth_CH6;

  radio.write(&Array,sizeof(Array));*/
}
