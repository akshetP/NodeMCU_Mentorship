#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
#define led D5
#define led2 D6
void setup() 
{
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
  server.begin();
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}
void loop() 
{
  client = server.available();   
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /led1on HTTP/1.1")
    {
      digitalWrite(led, HIGH);
    }
    if(request == "GET /led1off HTTP/1.1")
    {
      digitalWrite(led, LOW);
    }
    if(request == "GET /led2on HTTP/1.1")
    {
      digitalWrite(led2, HIGH);
    }
    if(request == "GET /led2off HTTP/1.1")
    {
      digitalWrite(led2, LOW);
    }
  }
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1><center>NodeMCU WebPage</center></h1>");
  client.println("<h3>LED Controller<h3>");
  client.println("<br>");
  client.println("<a href=\"/led1on\"\"><button>LED 1 ON</button></a>");
  client.println("<a href=\"/led1off\"\"><button>LED 1 OFF</button></a><br/>");
  client.println("<a href=\"/led2on\"\"><button>LED 2 ON</button></a>");
  client.println("<a href=\"/led2off\"\"><button>LED 2 OFF</button></a><br/>");
  client.println("</html>");
}
