#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(49000);
const char* ssid = "[SSID]";
const char* password = "[PASSWORD]";
const int led = 4;

void handleRoot() {
  Serial.println(server.argName(0)+server.arg(0));
  server.send(200, "text/plain", server.arg(0));
  if(server.arg(0)=="open"){
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
  }
 
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
