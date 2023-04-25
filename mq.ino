int sensorStatus;
int IRSensor = D1;

void setup(){
  pinMode(IRSensor, INPUT);
  Serial.begin(9600);
}
void loop(){
  sensorStatus = digitalRead(IRSensor);
  Serial.println(sensorStatus);
}
