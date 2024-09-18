#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "DHTesp.h" 

DHTesp dht;

const char* ssid = "Educere";
const char* password = "educere2023";

WebServer server(80);

void handleRoot() {
  float umidade = dht.getHumidity();
  float temperatura = dht.getTemperature();

  String response = String(umidade) + "e" + String(temperatura);
  server.send(200, "text/plain", response);
}

void handleNotFound() {
  String message = "File Not Found\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  dht.setup(14, DHTesp::DHT11); // GPIO14 (D5 no ESP8266) é o mesmo no ESP32
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Espera pela conexão Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(1500);

  float u = dht.getHumidity();
  float t = dht.getTemperature();

  Serial.print("Umidade (%): ");
  Serial.print(u, 1);
  Serial.print("\t");
  Serial.print("Temperatura (C): ");
  Serial.print(t, 1);
  Serial.print("\t");
  Serial.println();
}