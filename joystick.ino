int a = A0;
int b = A1;
int c = A2;
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(a));
  Serial.print(" , ");
  Serial.print(analogRead(b));
  Serial.print(" , ");
  Serial.println(analogRead(c));
  delay(10);
}
