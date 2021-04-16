#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
DHT dht(D5, DHT11);
WiFiClient client;
long myChannelNumber = ENTER_CHANNEL_ID;
const char myWriteAPIKey[] = "ENTER_KEY";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("ssid", "password");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(2000);
}
