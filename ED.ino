#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

void setup () {
  Serial.begin(115200);
  WiFi.begin("ED", "12345678");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected to WiFi Network");
}
void loop() {  
  if (WiFi.status() == WL_CONNECTED) { 
    WiFiClient client;
    HTTPClient http;
    http.begin(client,"http://192.168.228.150:80/esp_recieve");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "table=alarm";
    int httpCode = http.POST(httpRequestData);
    if (httpCode > 0) { 
      String payload = http.getString();
      Serial.println(payload);
    }else Serial.println("An error ocurred");
    http.end();
  }
  delay(100);
}
