#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int IRSensor = D4;
String payload_b="1";

void setup(){
  Serial.begin(115200);
  WiFi.begin("ED", "12345678");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected to WiFi Network");
  
  pinMode(IRSensor, INPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0,LOW);
}

void loop(){

  char prefix_a[20]="table=light";
  
  int sensorStatus = digitalRead(IRSensor);
  if(sensorStatus == 1){sensorStatus=0;}
  else{sensorStatus=1;}
  char mstatus[18];
  String temp_str = String(sensorStatus);
  temp_str.toCharArray(mstatus,2); 
  char prefix[20]="table=motion&Stat=";
  strcat(prefix, mstatus);
  if (WiFi.status() == WL_CONNECTED) { 
    WiFiClient client;
    HTTPClient http;
    http.begin(client,"http://192.168.20.154:8080/esp_send");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(prefix);
    if (httpCode > 0) { 
      String payload = http.getString();
      Serial.print("motion-");
      Serial.print(payload);
    }else {
      Serial.print("motion-An error ocurred");
      }

    
    http.begin(client,"http://192.168.20.154:8080/esp_recieve");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode_a = http.POST(prefix_a);
    if (httpCode_a > 0) { 
      payload_b = http.getString();
      Serial.print(" , light-");
      Serial.println(payload_b);
    }else{  
      Serial.println(" , light-An error ocurred");
      digitalWrite(D0,LOW);
    }
    http.end();

  if (payload_b == "1"){
    digitalWrite(D0,HIGH);
  }
  else if (payload_b == "0"){
    digitalWrite(D0,LOW);
  }
  
  }
  delay(100);
}
