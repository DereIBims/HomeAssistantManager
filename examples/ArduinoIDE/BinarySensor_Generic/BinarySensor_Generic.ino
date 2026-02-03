#include <Devices/BinarySensor.h>
#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// BinarySensor::Generic constructor: (manager, name, deviceClass)
HA::BinarySensor::Generic doorSensor(&Manager, "Door", HA::Door);

bool doorState = false;
unsigned long lastToggle = 0;

void setup() {
  Serial.begin(115200);
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
    doorSensor.setValue(doorState);
    lastToggle = millis();
  }
}
