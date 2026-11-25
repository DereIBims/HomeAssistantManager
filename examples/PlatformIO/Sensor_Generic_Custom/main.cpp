#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Sensor::Generic constructor: (manager, entity display name, sensor preset with default unit, state class)
HA::Sensor::Generic windSpeed(&Manager, "Wind Speed", "speed", "m/s", HA::MEASUREMENT);

void setup() {
  Serial.begin(115200);
  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
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
    // setValue(measured value, number of decimal places)
    windSpeed.setValue(6.42, 2);
    lastUpdate = millis();
  }
}
