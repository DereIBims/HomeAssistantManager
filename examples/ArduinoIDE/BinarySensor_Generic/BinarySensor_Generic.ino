#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// BinarySensor::Generic constructor: (manager, entity display name, Home Assistant binary sensor device class)
HA::BinarySensor::Generic doorSensor(&Manager, "Door", HA::Door);

bool doorState = false;
unsigned long lastToggle = 0;

void setup() {
  Serial.begin(115200);
  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32_Door", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  if (millis() - lastToggle > 3000) {
    doorState = !doorState;
    // setValue(door state, true = open and false = closed)
    doorSensor.setValue(doorState);
    lastToggle = millis();
  }
}
