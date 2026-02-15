#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Sensor::Generic constructor (custom class/unit): (manager, name, deviceClass, unit, stateClass)
HA::Sensor::Generic windSpeed(&Manager, "Wind Speed", "speed", "m/s", HA::MEASUREMENT);

void setup() {
  Serial.begin(115200);
  if (!Manager.begin("ESP32_Wind", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 5000) {
    windSpeed.setValue(6.42, 2);
    lastUpdate = millis();
  }
}
