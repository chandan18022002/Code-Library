#include <Adafruit_BME280.h>
Adafruit_BME280 bme;
float ip,p;
void setup() 
{
  Serial.begin(9600);
  if (!bme.begin(0x77)) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  ip = bme.readPressure() / 100.0F;
}

void loop()
{
  Serial.print("Altitude = ");
  p=bme.readAltitude(ip);
  Serial.print(p);
  Serial.println("m");
  delay(100);
}
