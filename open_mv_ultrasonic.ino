void setup() {
  pinMode(5,OUTPUT);    
  pinMode(4,OUTPUT);       
  pinMode(6,OUTPUT);    // trig
  pinMode(7,INPUT);     //echo
  Serial.begin(9600);

}

void loop() {
  
  digitalWrite(6,HIGH);
  delayMicroseconds(10);
  digitalWrite(6,LOW);
  int distance=pulseIn(7,HIGH);
  distance=(distance*0.17); 
  Serial.println(distance);
  if(distance>=100)
  {
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
  }
  else
  {
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
  }
  if(distance<100)
  {
    digitalWrite(6,LOW);
    delay(2000);
    digitalWrite(5,HIGH);
    delay(4000);
  }
  else{
    digitalWrite(6,HIGH);
  }
}
