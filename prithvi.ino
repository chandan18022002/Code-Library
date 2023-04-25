const int in1 = 2;
const int in2 = 3;
const int in3 = 8;
const int in4 = 9;
int di;
char b;
#define trigPin 7
#define echoPin 6
#define MD 50
#include <SharpIR.h>
SharpIR sensor1( SharpIR::GP2Y0A41SK0F, A0 );
SharpIR sensor2( SharpIR::GP2Y0A41SK0F, A1 );
void setup(){
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}
void left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void forwards(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void backwords() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void OFF(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void Distance(){
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration;
  duration = pulseIn(echoPin, HIGH);
  di = duration * 0.034 / 2;
  if( di>30 ){
    forwards();
    Serial.println("forward");
  }
  else if(di<20){
    backwords();
    Serial.println("backwords");
  }
 else{
  OFF();
  Serial.println("OFF");
 }
}
void loop(){
  if(digitalRead(10)==HIGH){
    int distance1 = sensor1.getDistance();
    int distance2 = sensor2.getDistance();
    if(((distance2 != 3) || (distance2 != 4) || (distance2 != 5) || (distance2 != 6) )&& ((distance1 == 3) || (distance1 == 4) || (distance1 == 5) || (distance1 == 6) || (distance1 == 7))) {
      left();
      Serial.println("left");
    }
    else if(((distance2 == 3) || (distance2 == 4) || (distance2 == 5) || (distance2 == 6))  && ((distance1 != 3) || (distance1 != 4) || (distance1 != 5) || (distance1 != 6) || (distance1 != 7))){
      right();
      Serial.println("right");
    }
    else if(((distance2 == 3) || (distance2 == 4) || (distance2 == 5) || (distance2 == 6))  &&( (distance1 == 3) ||(distance1 == 4) || (distance1 == 5) || (distance1 == 6) || (distance1 == 7))) {
      Distance();  
    }
    else if(((distance2 != 3) || (distance2 != 4) || (distance2 != 5) || (distance2 != 6)) && ((distance1 != 3) || (distance1 != 4) || (distance1 != 5) || (distance1 != 6) || (distance1 != 7))) {
      Distance(); 
    }
    else {
      Distance(); 
    }
    delay(100);
  }
  else if(digitalRead(10)==LOW){
    if(Serial1.available()>0){
      b=Serial1.read();
      if(b=='f'){
        forwards(); 
        Serial.println("forward");
        Serial1.println("forward");
      }
      if(b=='b'){
        backwords(); 
        Serial.println("backwords");
        Serial1.println("backwords");
      }
      if(b=='l'){
        left(); 
        Serial.println("left");
        Serial1.println("left");
      }
      if(b=='r'){
        right(); 
        Serial.println("right");
        Serial1.println("right");
      }
      if(b=='s'){
        OFF(); 
        Serial.println("OFF");
        Serial1.println("OFF");
      }
    }
  }
}
