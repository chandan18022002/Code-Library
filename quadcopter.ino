
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

#include <Servo.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(48, 49); // CE, CSN

Servo LF;
Servo LB;
Servo RB;
Servo RF;
//Servo MODE;

float elapsedTime, time, timePrev;

double sxp=1.1; //sensitity-p
double syp=1;
double szp=5;

double sxi=0.00; //sensitity-i
double syi=1;
double szi=5;

double sxd=1; //sensitity-d
double syd=1;
double szd=5;

const byte address[6] = "00001";
int max_height=200;    //Max Height
int pitch,Pitch,throttle,Throttle,Yaw,yaw,Roll,roll,Mode,mode,Mode1,mode1,lfv,lbv,rbv,rfv=0;
float Xangle,xangle,xangle_p,xangle_i,xangle_d,Yangle,yangle,yangle_p,yangle_i,yangle_d,Zangle,zangle,zangle_p,zangle_i,zangle_d,iXangle,iYangle,iZangle,error_x,error_y,error_z,p_error_x,p_error_y,p_error_z=0;
short Array[8];

#define echoPin 47  //ultrasonic
#define trigPin 45

long duration;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);  // wait for serial port to open!
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
  
  pinMode(13,OUTPUT);
  
  LF.attach(12);
  LB.attach(11);
  RB.attach(10);
  RF.attach(9);
  
  LF.writeMicroseconds(1000);
  LB.writeMicroseconds(1000+300);
  RB.writeMicroseconds(1000);
  RF.writeMicroseconds(1000);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("");
  delay(4000);
  time = millis();
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  iXangle=euler.x();
  iYangle=euler.y();
  iZangle=euler.z();
  if(iXangle<=360.00 and iXangle>180.00){
    iXangle=iXangle-360.00;
    }
}

void loop() {
  timePrev = time;
  time = millis();
  elapsedTime = (time - timePrev) / 1000; 
    
  if (radio.available()) {

    radio.read(&Array,sizeof(Array));

    Yaw=Array[0];//Yaw
    //yaw=Yaw;
    yaw=map(Yaw, 986, 82, -28, 30);

    Throttle=Array[1];//Throttle
    throttle=map(Throttle, 60, 1010, 1000, 2000);

    Roll=Array[2];//Roll
    //roll=Roll;
    roll=map(Roll, 983, 26, -29, 30);

    Pitch=Array[3];//Pitch
    //pitch=Pitch;
    pitch=map(Pitch, 1011, 63, -28, 30);
    pitch=-pitch;

    Mode=Array[6];//Mode
    mode=map(Mode, 1023, 0, 1000, 2000);

    Mode1=Array[7];//Mode1
    mode1=map(Mode1, 1023, 0, 1000, 2000);

//    Serial.print(Array[0]);
//    Serial.print(" , ");
//    Serial.print(Array[1]);
//    Serial.print(" , ");
//    Serial.print(Array[2]);
//    Serial.print(" , ");
//    Serial.print(Array[3]);
//    Serial.print(" , ");
//    Serial.print(Array[6]);
//    Serial.print(" , ");
//    Serial.print(Array[7]);

    Serial.print(" ,|,  ");
    Serial.print(yaw);
    Serial.print(" , ");
    Serial.print(throttle);
    Serial.print(" , ");
    Serial.print(roll);
    Serial.print(" , ");
    Serial.print(pitch);
    Serial.print(" , ");
    Serial.print(mode);
    Serial.print(" , ");
    Serial.print(mode1);


    digitalWrite(13,HIGH);
    }
  else{
    roll = 0;
    pitch = 0;
    yaw = 0;
    mode=1000;
    mode1=2000;
    digitalWrite(13,LOW);
    }
  /*
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Height = (duration * 0.034 / 2) - 2;
  */

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  Xangle=euler.x();
  Yangle=euler.y();
  Zangle=euler.z();
  if(Xangle<=360.00 and Xangle>180.00){
    Xangle=Xangle-360.00;
    }
    
  if(mode>1500){
    error_x=(Zangle-roll-iZangle);//roll
    error_y=(Yangle-pitch-iYangle);//pitch
    error_z=(Xangle-yaw-iXangle);//yaw
  }
  else{
    error_x=(Zangle-roll);//roll
    error_y=(Yangle-pitch);//pitch
    error_z=(Xangle-yaw);//yaw
    }

  xangle_p = sxp*error_x;
  
  if(-6 <xangle <6){
    xangle_i = xangle_i+(sxi*error_x);  
    }
  else{
    xangle_i=0;
  }

  xangle_d = sxd*((error_x - p_error_x)/elapsedTime);

  xangle = xangle_p + xangle_i + xangle_d;
  
  if(mode1>1500){
    lfv=1000;
    lbv=1000;
    rbv=1000;
    rfv=1000;
  }
  else{
    lfv=throttle+xangle;//+yangle+zangle;
    lbv=throttle+xangle;//-yangle-zangle;
    rbv=throttle-xangle;//-yangle+zangle;
    rfv=throttle-xangle;//+ yangle-zangle;
    }
    
  Serial.print(" ,|,  ");
  Serial.print(Zangle);
//  Serial.print(" , ");
//  Serial.print(Yangle);
//  Serial.print(" , ");
//  Serial.print(Xangle);
  Serial.print(" , ");
  Serial.print(xangle);
//  Serial.print(" , ");
//  Serial.print(yangle);
//  Serial.print(" , ");
//  Serial.print(zangle);
  
  Serial.print(" ,|,  ");
  Serial.print(lfv);
  Serial.print(" , ");
  Serial.print(lbv);
  Serial.print(" , ");
  Serial.print(rbv);
  Serial.print(" , ");
  Serial.println(rfv);
  
  LF.writeMicroseconds(lfv+10);
  LB.writeMicroseconds(lbv+300);
  RB.writeMicroseconds(rbv+20);
  RF.writeMicroseconds(rfv+10);
  
  p_error_x = error_x;
  p_error_y = error_y;
  p_error_z = error_z;
 delay(10);
}
