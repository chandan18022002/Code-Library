#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;
float temp;

void setup() {
  Serial.begin(9600);
  
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin(); 
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D8, OUTPUT);
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    if (tag == "1126719527" or tag == "3519685167" or tag == "49348170") {
      temp=mlx.readObjectTempC();
      Serial.print("temperature =");
      Serial.println(temp);
      if(temp>30 and temp<40){
        Serial.println("Access Granted");
        digitalWrite(D8, HIGH);
        delay(100);
        digitalWrite(D8, LOW);
        delay(100);
        digitalWrite(D8, HIGH);
        delay(100);
        digitalWrite(D8, LOW);
        delay(100);
        digitalWrite(D8, HIGH);
        delay(100);
        digitalWrite(D8, LOW);
        delay(100);
      } else {
        Serial.println("Access Denied!");
        digitalWrite(D8, HIGH);
        delay(2000);
        digitalWrite(D8, LOW);
      }
    } else {
      Serial.println("Access Denied!");
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(D8, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
