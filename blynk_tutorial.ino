//Tech Trends Shameer
//Control LED Using Blynk 2.0/Blynk IOT

#define BLYNK_TEMPLATE_ID "TMPLEOk-mF-m"
#define BLYNK_DEVICE_NAME "LED"
#define BLYNK_AUTH_TOKEN "z9IPyXKmukrjqbl0dMo4DaEgGwyz7XhZ"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = " ";  // Enter your Wifi Username
char pass[] = "12345678";  // Enter your Wifi password

int ledpin = D4;
void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  Blynk.run(); 
}
