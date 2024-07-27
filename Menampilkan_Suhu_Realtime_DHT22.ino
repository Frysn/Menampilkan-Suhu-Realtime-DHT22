// ||=================================||
// ||      CREAT by FERY SETIAWAN     ||
// ||     Technology of Univercity    ||
// ||           YOGYAKARTA            ||
// ||=================================||
// 27/07/2024



#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#include "Page.h"

// Pengaturan WiFi
const char* ssid = "Fry_sn";
const char* password = "16062k04";

// Pengaturan DHT
#define DHTPIN 4    // Pin yang terhubung ke DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi server
AsyncWebServer server(80);

// Mengubah data sensor ke format JSON
String getDataJson() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  String json = "{\"temperature\":";
  json += temperature;
  json += ",\"humidity\":";
  json += humidity;
  json += "}";
  return json;
}

void setup() {
  // Memulai Serial Monitor
  Serial.begin(115200);

  // Memulai DHT sensor
  dht.begin();

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Mengatur route untuk menyajikan file HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Mengatur route untuk mengakses data sensor
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/json", getDataJson());
  });

  // Memulai server
  server.begin();
}

void loop() {
  // Kosong karena server bekerja secara asynchronous
}
