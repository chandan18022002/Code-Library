#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(48,49); // CE, CSN

const byte address[6] = "00001";
short Array[8];
int a = A0;
int b = A1;
int c = A2;
int d = A3;
int e = A4;
int f = A5;
int g = A7;
int h = A8;

void setup(void) {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  Array[0]=analogRead(a);//505
  Array[1]=analogRead(b);//504
  Array[2]=analogRead(c);//!0
  Array[3]=analogRead(d);//497
  Array[4]=analogRead(e);//506
  Array[5]=analogRead(f);//
  Array[6]=analogRead(g);//506
  Array[7]=analogRead(h);//

  radio.write(&Array,sizeof(Array));
  
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
  Serial.println(Array[7]);
  
  delay(1);
}
