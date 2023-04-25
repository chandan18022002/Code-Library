#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif
WiFiServer server(80);
#include <Wire.h>
const char* ssid     = "KLE";
const char* password = "12345678";
char prefix[20] = "W_Status=";

const char* serverName = "https://myautomower.000webhostapp.com:80/Status.php";
String get_host = "https://myautomower.000webhostapp.com:80";
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "Object Has Been Detected!!!";

#define SEALEVELPRESSURE_HPA (1013.25)

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  if (Serial.available() > 0) {
    //char v=Serial.read();
    char mstatus[18];
    String temp_str = String(Serial.read());
//    temp_str.toCharArray(mstatus, 2);
//    char prefix[20] = "W_Status=";
//    strcat(prefix, mstatus);
    Serial.println(temp_str);
  //}
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "W_Status=" + temp_str  ;
//    Serial.print("httpRequestData: ");
//    Serial.println(prefix);//httpRequestData);
    int httpResponseCode = http.POST(temp_str);//httpRequestData);
    if (httpResponseCode > 0) {
//      Serial.print("HTTP Response code: ");
//      Serial.print(httpResponseCode);
//      Serial.print(" , ");
      String p = http.getString();
      Serial.println(p);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    get_device_status("Emergency", "Emergency_Button");
    record_status("Command");
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(5000);
} else {
  Serial.println("serial not detected");
}
}

void get_device_status(String device_name, String device_text)
{

  WiFiClient client = server.available();

  HTTPClient http;
  String url = get_host + "/get_emergency.php?Button_name=" + device_name;

  http.begin(client, url);



  //GET method
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println("Emrgency" + payload);
  if (payload == "1")
  {
    Serial.println(device_text + " is ON");
  }
  else
  {
    Serial.println(device_text + " is Off");
  }
  http.end();
  delay(1000);

}
void record_status(String device_name)
{

  WiFiClient client = server.available();

  HTTPClient http;
  String url = get_host + "/getRecord.php?Command=" + device_name;

  http.begin(client, url);

  //GET method
  int httpCode = http.GET();
  String payload1 = http.getString();
  Serial.println("Emrgency" + payload1);
  if (payload1 == "B")
  {
    Serial.println("Backward");
  }
  else if (payload1 == "F")
  {
    Serial.println("Forward");
  }
  else if (payload1 == "R")
  {
    Serial.println("Right");
  }
  else if (payload1 == "L")
  {
    Serial.println("Left");
  }
  else if (payload1 == "S")
  {
    Serial.println("Stop");
  }
  else {
    Serial.println("Didn't Receive");

  }
  http.end();
  delay(1000);

}
