#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host", LOG_LEVEL_INFO);

// Sensor::Generic constructor: (manager, entity display name, sensor preset with default unit, state class)
HA::Sensor::Generic temperature(&Manager, "Temperature", HA::Temperature, HA::MEASUREMENT);

// Sensor::Generic constructor: (manager, entity display name, sensor preset with default unit, state class)
HA::Sensor::Generic customPower(&Manager, "Power Raw", "power", "W", HA::MEASUREMENT);

// BinarySensor::Generic constructor: (manager, entity display name, Home Assistant binary sensor device class)
HA::BinarySensor::Generic motion(&Manager, "Motion", HA::Motion);

// Button::Generic constructor: (manager, entity display name, diagnostic category = false)
HA::Button::Generic testButton(&Manager, "Test Button");

unsigned long lastSensorUpdate = 0;
unsigned long lastMotionToggle = 0;
bool motionState = false;

void onTestButton() {
  Serial.println("Test button pressed");
}

void setup() {
  Serial.begin(115200);

  // setMqttPort(MQTT broker TCP port)
  Manager.setMqttPort(1883);
  // setMqttCredentials(MQTT username, MQTT password)
  Manager.setMqttCredentials("mqtt-user", "mqtt-pass");
  // setAutoDiagInterval(update interval in milliseconds)
  Manager.setAutoDiagInterval(20000);

  // setCommandCallback(function called on button press, with no arguments)
  testButton.setCommandCallback(onTestButton);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32_Multi", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();

  if (millis() - lastSensorUpdate > 5000) {
    // setValue(measured value, number of decimal places)
    temperature.setValue(22.5, 1);
    // setValue(measured value, number of decimal places)
    customPower.setValue(123.4, 1);
    lastSensorUpdate = millis();
  }

  if (millis() - lastMotionToggle > 3000) {
    motionState = !motionState;
    // setValue(motion state, true = detected and false = clear)
    motion.setValue(motionState);
    lastMotionToggle = millis();
  }
}
