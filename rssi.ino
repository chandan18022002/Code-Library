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
    long rssi = WiFi.RSSI();
    Serial.print("RSSI:");
    Serial.println(rssi);
  }
  delay(100);
}
