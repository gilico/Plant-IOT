#include <ArduinoJson.h>

bool test_connection(int attempts) {
  Serial.println("test_connection");
  bool access = false;
  String url = endpoint + serial_num + "/test-connection";

  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, url.c_str());
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      DynamicJsonDocument doc(2048);
      String response = http.getString();
      deserializeJson(doc, response);
      access = doc["access"];
    } else {
      Serial.println("failed: ");
      Serial.println(http.errorToString(httpCode));
      return test_connection(attempts++);
    }

    http.end();
  } else {
    wifi_Setup();
    return test_connection(attempts++);
  }
  return access;
}


void need_water_request(int attempts) {
  if (WiFi.status() == WL_CONNECTED) {
    String url = endpoint + serial_num + "/need-water";
    http.begin(client, url.c_str());
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      Serial.println("Update water request");
    } else {
      Serial.println("failed: ");
      Serial.println(http.errorToString(httpCode));
      return need_water_request(attempts++);
    }
    http.end();
  } else {
    wifi_Setup();
    return need_water_request(attempts++);
  }
}
