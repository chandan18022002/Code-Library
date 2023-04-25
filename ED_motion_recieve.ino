#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int smoke = D0;
int buzzer = D2;
int pump = D1;
String payload_b="1";
String payload_p="1";
void setup(){
  Serial.begin(115200);
  WiFi.begin("ED", "12345678");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected to WiFi Network");
  
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  pinMode(pump, OUTPUT);
  digitalWrite(pump,HIGH);
  pinMode(smoke, INPUT);
}

void loop(){

  char prefix_a[20]="table=alarm";
  
  char prefix_f[20]="table=fire";
  
  int sensorStatus = digitalRead(smoke);
  if(sensorStatus == 1){sensorStatus=0;}
  else{sensorStatus=1;}
  char mstatus[18];
  String temp_str = String(sensorStatus);
  temp_str.toCharArray(mstatus,2); 
  char prefix[20]="table=smoke&Stat=";
  strcat(prefix, mstatus);
  
  if (WiFi.status() == WL_CONNECTED) { 
    WiFiClient client;
    HTTPClient http;
    http.begin(client,"http://192.168.20.154:8080/esp_recieve");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode_a = http.POST(prefix_a);
    if (httpCode_a > 0) { 
      payload_b = http.getString();
      Serial.print("buzzer-");
      Serial.print(payload_b);
    }else{  
      Serial.print("buzzer-An error ocurred");
      digitalWrite(buzzer,HIGH);
    }
    //http.end;
    
    http.begin(client,"http://192.168.20.154:8080/esp_recieve");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode_f = http.POST(prefix_f);
    if (httpCode_f > 0) { 
      payload_p = http.getString();
      Serial.print(" , fire-");
      Serial.print(payload_p);
    }else{
      Serial.print(" , fire-An error ocurred");
      digitalWrite(pump,HIGH);
    }
    //http.end;
    
    http.begin(client,"http://192.168.20.154:8080/esp_send");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    int httpCode = http.POST(prefix);
    if (httpCode > 0) { 
      String payload = http.getString();
      Serial.print(" , smoke-");
      Serial.println(payload);
    }else 
      Serial.println(" , smoke-An error ocurred");
    
    http.end();
  }
  
  if (payload_b == "1"){
    digitalWrite(buzzer,LOW);
  }
  else if (payload_b == "0"){
    digitalWrite(buzzer,HIGH);
  }
  
  if (payload_p == "1"){
    digitalWrite(pump,LOW);
  }
  else if (payload_p == "0"){
    digitalWrite(pump,HIGH);
  }
  
  delay(100);
}
