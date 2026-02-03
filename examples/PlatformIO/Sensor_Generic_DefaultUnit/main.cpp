#include <Devices/Sensor.h>
#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost, logLevel)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host", LOG_LEVEL_INFO);

// Sensor::Generic constructor (default unit): (manager, name, SensorClass, stateClass)
HA::Sensor::Generic temperature(&Manager, "Temperature", HA::Temperature, HA::MEASUREMENT);

void setup() {
  Serial.begin(115200);
  if (!Manager.begin("ESP32_Temp", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  temperature.setValue(23.7, 1);
  delay(5000);
}
