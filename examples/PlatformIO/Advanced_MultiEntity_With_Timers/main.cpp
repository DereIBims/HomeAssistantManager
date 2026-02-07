#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost, logLevel)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host", LOG_LEVEL_INFO);

// Sensor::Generic constructor (default unit): (manager, name, SensorClass, stateClass)
HA::Sensor::Generic temperature(&Manager, "Temperature", HA::Temperature, HA::MEASUREMENT);

// Sensor::Generic constructor (custom class/unit): (manager, name, deviceClass, unit, stateClass)
HA::Sensor::Generic customPower(&Manager, "Power Raw", "power", "W", HA::MEASUREMENT);

// BinarySensor::Generic constructor: (manager, name, deviceClass)
HA::BinarySensor::Generic motion(&Manager, "Motion", HA::Motion);

// Button::Generic constructor: (manager, name)
HA::Button::Generic testButton(&Manager, "Test Button");

unsigned long lastSensorUpdate = 0;
unsigned long lastMotionToggle = 0;
bool motionState = false;

void onTestButton() {
  Serial.println("Test button pressed");
}

void setup() {
  Serial.begin(115200);

  Manager.setMqttPort(1883);
  Manager.setMqttCredentials("mqtt-user", "mqtt-pass");
  Manager.setAutoDiagInterval(20000);

  testButton.setCommandCallback(onTestButton);

  if (!Manager.begin("ESP32_Multi", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();

  if (millis() - lastSensorUpdate > 5000) {
    temperature.setValue(22.5, 1);
    customPower.setValue(123.4, 1);
    lastSensorUpdate = millis();
  }

  if (millis() - lastMotionToggle > 3000) {
    motionState = !motionState;
    motion.setValue(motionState);
    lastMotionToggle = millis();
  }
}
