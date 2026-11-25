#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");
// Number::Generic constructor: (manager, entity display name, minimum, maximum, step size, unit)
HA::Number::Generic interval(&Manager, "Sample Interval", 1, 60, 0.5, "s");

void onIntervalCommand(float seconds) {
  Serial.print("Sample interval set to ");
  Serial.println(seconds);
  // setValue(confirmed interval in seconds)
  interval.setValue(seconds); // Confirm the value after the application accepts it.
}

void setup() {
  Serial.begin(115200);

  // setCommandCallback(function receiving the requested number as a float)
  interval.setCommandCallback(onIntervalCommand);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32 Number", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }

  // setValue(confirmed interval in seconds)
  interval.setValue(5);
}

void loop() {
  Manager.loop();
}
