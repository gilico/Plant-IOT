#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Kinneret";
//const char* pswd = "Aa787878";
const String endpoint = "http://gil.ngrok.app/api/arduino/";

WiFiClient client;
HTTPClient http;

void wifi_Setup() {
  Serial.println("wifiSetup");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("trying...");
    delay(100);
  }
  Serial.println("Connected to network");
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}
