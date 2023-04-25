#include <Servo.h>

Servo myservo;
void setup() {
  myservo.attach(7);
}

void loop() {
  myservo.write(90);
}
