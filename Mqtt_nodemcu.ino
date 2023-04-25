#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// GPIO 5 D1
#define LED 5

// WiFi
const char *ssid = " "; // Enter your WiFi name
const char *password = "12345678";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.mqttdashboard.com";
const char *topic = "test";
const char mqtt_username[] = "chandan";
const char mqtt_password[] = "12345678";
const int mqtt_port = 8000;

char Buf[32];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);
    // connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        client_id.toCharArray(Buf, client_id.length());
        Serial.println("Connecting to public emqx mqtt broker.....");
        if (client.connect(Buf, mqtt_username, mqtt_password)) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    client.publish(topic, "hello emqx");
    client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    String message;
    for (int i = 0; i < length; i++) {
        message = message + (char) payload[i];  // convert *byte to string
    }
    Serial.print(message);
    if (message == "on") { digitalWrite(LED, LOW); }   // LED on
    if (message == "off") { digitalWrite(LED, HIGH); } // LED off
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
    client.loop();
}
