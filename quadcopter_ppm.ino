#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(48, 49); // CE, CSN

int s=2; //sensitity

const byte address[6] = "00001";
int max_height=200;    //Max Height
int pitch,Pitch,throttle,Throttle,Yaw,yaw,Roll,roll,y,t,r,p,m,m1,height,iheight,Height,ix,iy,iz,Mode,mode,Mode1,mode1,Switch1,switch1,Switch2,switch2 = 0;
float Xangle,xangle,Yangle,yangle,Zangle,zangle=0;
short Array[8];

#define echoPin 47  //ultrasonic
#define trigPin 45

long duration;

#define CHANNEL_NUMBER 8  //set the number of chanels
#define CHANNEL_DEFAULT_VALUE 1500  //set the default servo value
#define FRAME_LENGTH 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PULSE_LENGTH 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 7  //set PPM signal output pin on the 

int ppm[CHANNEL_NUMBER];

void setup(void) {
  Serial.begin(115200);
  
  pinMode(13,OUTPUT);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("");

  
  //initiallize default ppm values
  for(int i=0; i<CHANNEL_NUMBER; i++){
      ppm[i]= CHANNEL_DEFAULT_VALUE;
  }

  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)
  
  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;
  
  OCR1A = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
}

void loop() {
  
  if (radio.available()) {

    radio.read(&Array,sizeof(Array));
    
    Yaw=Array[0];//Yaw
    yaw=map(Yaw, 986, 70, 1000, 2000);

    Throttle=Array[1];//Throttle
    throttle=map(Throttle, 70, 1010, 1000, 2000);

    Roll=Array[2];//Roll
    roll=map(Roll, 985, 26, 1000, 2000);
    
    Pitch=Array[3];//Pitch
    pitch=map(Pitch, 1010, 63, 1000, 2000);

    Mode=Array[5];//Mode
    mode=map(Mode, 1023, 0, 1000, 2000);

    Mode1=Array[4];//Mode1
    mode1=map(Mode1, 1023, 0, 1000, 2000);

    Switch2=Array[6];//Switch2
    switch2=map(Switch2, 1023, 0, 1000, 2000);

    Switch1=Array[7];//Switch1
    switch1=map(Switch1, 1023, 0, 1000, 2000);
   /*
    Serial.print(Array[0]);
    Serial.print(" , ");
    Serial.print(Array[1]);
    Serial.print(" , ");
    Serial.print(Array[2]);
    Serial.print(" , ");
    Serial.print(Array[3]);
    Serial.print(" , ");
    Serial.print(Array[4]);
    Serial.print(" , ");
    Serial.print(Array[5]);
    Serial.print(" , ");
    Serial.print(Array[6]);
    Serial.print(" , ");
    Serial.print(Array[7]);
  */
    
    digitalWrite(13,HIGH);
    }
  else{
    roll = 1500;
    pitch = 1500;
    yaw = 1500;
    mode=1000;
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
  
    ppm[3]=yaw;
    ppm[2]=throttle;
    ppm[0]=roll;
    ppm[1]=pitch;
    ppm[4]=switch1;
    ppm[5]=mode1;
    if(switch1==1000 and switch2==1000 ){
      ppm[6]=1600;
      }
    else if(switch2==2000 and switch1==1000){
      ppm[6]=1180;
      }
    else{
      ppm[6]=1846;
      }
    ppm[7]=switch2;
    
    Serial.print(" ,|,  ");
    Serial.print(ppm[0]);
    Serial.print(" , ");
    Serial.print(ppm[1]);
    Serial.print(" , ");
    Serial.print(ppm[2]);
    Serial.print(" , ");
    Serial.print(ppm[3]);
    Serial.print(" , ");
    Serial.print(ppm[4]);
    Serial.print(" , ");
    Serial.print(ppm[5]);
    Serial.print(" , ");
    Serial.print(ppm[6]);
    Serial.print(" , ");
    Serial.println(ppm[7]);
    
 delay(10);
}

ISR(TIMER1_COMPA_vect){  //leave this alone
  static boolean state = true;
  
  TCNT1 = 0;
  
  if (state) {  //start pulse
    digitalWrite(sigPin, onState);
    OCR1A = PULSE_LENGTH * 2;
    state = false;
  } else{  //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;
  
    digitalWrite(sigPin, !onState);
    state = true;

    if(cur_chan_numb >= CHANNEL_NUMBER){
      cur_chan_numb = 0;
      calc_rest = calc_rest + PULSE_LENGTH;// 
      OCR1A = (FRAME_LENGTH - calc_rest) * 2;
      calc_rest = 0;
    }
    else{
      OCR1A = (ppm[cur_chan_numb] - PULSE_LENGTH) * 2;
      calc_rest = calc_rest + ppm[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
}
