#include <Servo.h>
Servo myservo;
char d;

void setup() {
  pinMode(5,OUTPUT);    
  pinMode(4,OUTPUT);       
  pinMode(6,OUTPUT);    // trig
  pinMode(7,INPUT);     //echo
  
  myservo.attach(9); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0,INPUT);
  Serial1.begin(19200);
  Serial.begin(19200);
 }
 
 void loop() {
  /*
  digitalWrite(6,HIGH);
  delayMicroseconds(10);
  digitalWrite(6,LOW);
  int distance=pulseIn(7,HIGH);
  distance=(distance*0.17); 
  Serial.println(distance);
  */
  int i=0;
  int p=analogRead(A0);
  if(p == 0){
    
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
    
    //Serial.println("zero");
    Serial1.print("1");
    while(i==0 and p==0){
      //Serial.print("-in-");
      p=analogRead(A0);
      if (Serial1.available()>0){
        d = Serial1.read();
        //Serial.println(Serial1.available());
        if (d == 'a'){
          i=1;         
          //Serial.write("LED IS OFF");
          digitalWrite(LED_BUILTIN, LOW);
          Serial.println("Servo execute");
          delay(3000);
        }
        if (d == 'b'){ 
          i=1;                 
          //Serial.write("LED IS OFF");
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("Servo Don't execute");
          delay(3000);
        }
      }
    }
    Serial.println("start motor");
    delay(4000);
    
  }
  else{
    
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    
    Serial.println("not zero");
    }
    
}
