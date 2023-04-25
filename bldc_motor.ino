#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue,potValue1;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
  Serial.begin(115200);
  ESC.attach(10); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue1 = map(potValue, 0, 800, 1000, 2000);   // scale it to use it with the servo library (value between 0 and 180)
  Serial.print(potValue);
  Serial.print(" , ");
  Serial.println(potValue1);
  ESC.write(potValue1);    // Send the signal to the ESC
}
