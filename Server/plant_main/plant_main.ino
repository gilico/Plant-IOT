unsigned long previousTime = 0;  // Variable to store the previous time
unsigned long interval = 2 * 1000;  // 5 hours in milliseconds

//const int soilTemperaturePin = A0;  // Analog input pin for soil temperature
#define SOIL_HUMID_PID A3

String serial_num = "123456";
int water_amount = -1;
const int minHuidityVal = 50;

void setup() {
  Serial.begin(9600);
  delay(100);
  wifi_Setup();
}

void loop() {
  if (is_need_to_check_sensors()) {
    int soilHumidityValue = analogRead(A4); // Read soil humidity
    Serial.println(soilHumidityValue);
    float humidity = map(soilHumidityValue, 4096, 0, 0, 100);// Humidity range (0% to 100%)
    Serial.print("Soil Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // If the plant hit the minimum alowed value of soil humidity
    if (humidity <= minHuidityVal) {
      bool isConnect = test_connection(0);
      if (isConnect) {
        // Request water
        need_water_request(0);        
      }
    }
  }
}


bool is_need_to_check_sensors() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;  // Update the previous time
    Serial.println("TIME!!!");
    return true;
  }
  return false;
}
