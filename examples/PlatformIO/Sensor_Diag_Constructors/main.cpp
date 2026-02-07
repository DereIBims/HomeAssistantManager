#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Sensor::Diag constructor (default unit): (manager, name, SensorClass, stateClass)
HA::Sensor::Diag diagBattery(&Manager, "Battery Level", HA::Battery, HA::MEASUREMENT);

// Sensor::Diag constructor (custom class/unit): (manager, name, deviceClass, unit, stateClass)
HA::Sensor::Diag diagText(&Manager, "Custom Diag Text", nullptr, nullptr, HA::MEASUREMENT);

void setup() {
  Serial.begin(115200);
  if (!Manager.begin("ESP32_Diag", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  diagBattery.setValue(88);
  diagText.setState("OK");
  delay(5000);
}
