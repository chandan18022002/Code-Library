#include <Arduino.h>
#include <TinyMPU6050.h>

#include <Servo.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

MPU6050 mpu (Wire);
unsigned long timer = 0;

RF24 radio(7, 8); // CE, CSN

Servo ls;
Servo rs;
Servo lm;
Servo rm;

const byte address[6] = "00001";
int pitch,Pitch,throttle,Throttle,Yaw,yaw,Roll,roll,lsv,rsv,lmv,rmv,Xangle,xangle,Yangle,yangle,Zangle,zangle = 0;
int reset = 200;
//float  = 0;
short Array[5];

void setup(void) {
  Serial.begin(115200);
  /*
  mpu.Initialize();
  
  // Calibration
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");*/
  
  ls.attach(13);
  ls.write(90);
  rs.attach(12);
  rs.write(90);
  lm.attach(11);
  lm.write(1000);
  rm.attach(10);
  rm.write(1000);
  lsv=90;
  rsv=90;
  lmv=1000;
  rmv=1000;
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("");
  delay(100);
}

void loop() {
  
  if (radio.available()) {

    radio.read(&Array,sizeof(Array));
    Roll=Array[0];//Roll
    roll=Roll;
    roll-=504;
    roll/=1;
    
    Pitch=Array[1];//Pitch
    pitch=Pitch;
    pitch-=504;
    pitch/=1;
    
    reset = Array[2];//button
    
    Throttle=Array[3];//Throttle
    
    Yaw=Array[4];//Yaw
    yaw=Yaw;
    yaw-=507;
    yaw/=1;
   
    Serial.print(Array[0]);//50(4,3)
    Serial.print(" , ");
    Serial.print(Array[1]);//50(4,3)
    Serial.print(" , ");
    Serial.print(Array[2]);//!0
    Serial.print(" , ");
    Serial.print(Array[3]);//48(7,8)
    Serial.print(" , ");
    Serial.print(Array[4]);//50(7,6)
    }
  else{
    roll = 0;
    pitch = 0;
    yaw = 0;
    reset = 200;
    }
  /*
  mpu.Execute();
  
  Xangle = mpu.GetAngX();
  Yangle = mpu.GetAngY();
  Zangle = mpu.GetAngZ();

  xangle=90+Xangle;
  yangle=90+Yangle;
  zangle=Zangle;
  
  lsv= yangle + zangle;
  rsv= yangle - zangle;*/

  throttle=map(Throttle, 0, 800, 1000, 2000);
  lmv=throttle;
  rmv=throttle;

  //ls.write(lsv);
  //rs.write(rsv);
  //lm.write(lmv);
  rm.write(rmv);
  Serial.print(" , ");
  Serial.print(throttle);//48(7,8)
  Serial.print(" , ");
  Serial.println(Throttle);//50(7,6)
      
  delay(50);
  Serial.println("");
}
