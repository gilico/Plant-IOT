#define PUMP_INPUT D1

unsigned long previousTime = 0;  // Variable to store the previous time
unsigned long checkForWateringInterval = 15 * 1000;  // 5 hours in milliseconds

String serial_num = "123456";
int water_amount = -1;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(PUMP_INPUT, OUTPUT);
  digitalWrite(PUMP_INPUT, HIGH);
  wifi_Setup();
}

void loop() {
  if (is_time_passed_interval(checkForWateringInterval)) {
    bool isConnect = test_connection(0);
    if (isConnect) {
      // Request water amount from server to ensure the amount
      int waterAmountBySeconds = request_water_amount(0);
      Serial.print("water amount: ");
      Serial.println(waterAmountBySeconds);

      // Water the plant by digital output.
      activate_water_pump(waterAmountBySeconds);

//      if (waterAmountBySeconds > 0) {
        // Send a request to the server to update the watering time.
        update_watering_time(0);
//      }
    }
  }
}


void activate_water_pump(int waterAmountBySeconds) {
  unsigned long wateringInreval = waterAmountBySeconds * 1000;
  if (!is_time_passed_interval(wateringInreval)) {
    digitalWrite(PUMP_INPUT, LOW);
    Serial.println("HIGH!!!");
  } else {
    digitalWrite(PUMP_INPUT, HIGH);
    Serial.println("LOW!!!");
  }
}

bool is_time_passed_interval(int interval) {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;  // Update the previous time
    Serial.println("TIME!!!");
    return true;
  }
  return false;
}
