int i=0;
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
}
void loop() {
  if(i>=9){
    i=0;
    }
  i+=1;
  Serial1.println(i);
  Serial.println(i);
  delay(1000);
}
