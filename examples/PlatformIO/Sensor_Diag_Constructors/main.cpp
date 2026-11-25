#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Sensor::Diag constructor: (manager, entity display name, sensor preset with default unit, state class)
HA::Sensor::Diag diagBattery(&Manager, "Battery Level", HA::Battery, HA::MEASUREMENT);

// Sensor::Diag constructor: (manager, entity display name, device class = none here, unit = none here, state class = none here)
HA::Sensor::Diag diagText(&Manager, "Custom Diag Text", nullptr, nullptr, nullptr);

void setup() {
  Serial.begin(115200);
  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32_Diag", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 5000) {
    // setValue(battery level in percent)
    diagBattery.setValue(88);
    // setState(text published as the sensor state)
    diagText.setState("OK");
    lastUpdate = millis();
  }
}
