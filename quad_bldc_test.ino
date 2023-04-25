#include <Servo.h>

Servo q;
Servo w;
Servo e;
Servo r;


void setup() {
  q.attach(12);
  w.attach(11);
  e.attach(10);
  r.attach(9);
}

void loop() {
  q.write(1100);
  w.write(1100);
  e.write(1100);
  r.write(1100);
}
