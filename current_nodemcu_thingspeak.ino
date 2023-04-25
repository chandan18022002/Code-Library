#include <ESP8266WiFi.h>
 
String apiKey = "1YLVTCNTJCYIAKWD";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  " ";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
const char* server = "api.thingspeak.com";

WiFiClient client;

const int sensorIn = A0;      // pin where the OUT pin from sensor is connected on Arduino
int mVperAmp = 185;           // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
 
 
void setup() {
  Serial.begin (9600); 
  Serial.println("Connecting to ");
  Serial.println(ssid);
  
  
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
     
}
 
void loop() {
 
  Serial.println ("");
  
  Voltage = getVPP();
  VRMS = (Voltage/2.0) *0.707;   //root 2 is 0.707
  AmpsRMS = (VRMS * 1000)/mVperAmp;
  Watt = (AmpsRMS*240/1.3);      // 1.3 is an empirical calibration factor

  if (client.connect(server,80)){
    String postStr = apiKey;
    postStr +="&field4=";
    postStr += String(Watt);
    postStr += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.print(AmpsRMS);
    Serial.print(" Amps RMS  ---  ");
    Serial.print(Watt);
    Serial.println(" W");
    Serial.println("%. Send to Thingspeak.");
    }
  client.stop();
  
  Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
 
 
float getVPP()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
