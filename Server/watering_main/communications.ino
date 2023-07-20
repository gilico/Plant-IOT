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


int request_water_amount(int attempts) {
  Serial.println("request_water_amount");
  int waterAmountBySeconds = 0;
  String url = endpoint + serial_num + "/water-amount";

  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, url.c_str());
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      DynamicJsonDocument doc(2048);
      String response = http.getString();
      deserializeJson(doc, response);
      waterAmountBySeconds = doc["amount"];
    } else {
      Serial.println("failed: ");
      Serial.println(http.errorToString(httpCode));
      return request_water_amount(attempts++);
    }

    http.end();
  } else {
    wifi_Setup();
    return request_water_amount(attempts++);
  }
  return waterAmountBySeconds;
}


bool update_watering_time(int attempts) {
  Serial.println("request_water_amount");
  String url = endpoint + serial_num + "/update-watering";

  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, url.c_str());
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      return true;
    } else {
      Serial.println("failed: ");
      Serial.println(http.errorToString(httpCode));
      return update_watering_time(attempts++);
    }

    http.end();
  } else {
    wifi_Setup();
    return update_watering_time(attempts++);
  }
  return false;
}
