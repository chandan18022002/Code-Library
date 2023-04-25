#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

short Array[6];

void setup(void) {
  Serial.begin(115200);  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  
  if (radio.available()) {

    radio.read(&Array,sizeof(Array));
    
    
    Serial.print(Array[0]);//
    Serial.print(" , ");
    Serial.print(Array[1]);//
    Serial.print(" , ");
    Serial.print(Array[2]);//
    Serial.print(" , ");
    Serial.print(Array[3]);//
    Serial.print(" , ");
    Serial.print(Array[4]);//
    Serial.print(" , ");
    Serial.println(Array[5]);//
    }
}
