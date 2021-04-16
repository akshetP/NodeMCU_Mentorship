#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
#define led D5
void setup() 
{
  Serial.begin(9600);
  WiFi.softAP("ssid", "password");
  Serial.println();
  Serial.println("NodeMCU is Live!");
  Serial.println(WiFi.softAPIP());
  server.begin();
  pinMode(led, OUTPUT);
}
void loop() 
{
  client = server.available();    
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /ledon HTTP/1.1")
    {
      digitalWrite(led, HIGH);
    }
    if(request == "GET /ledoff HTTP/1.1")
    {
      digitalWrite(led, LOW);
    }
  }
}
