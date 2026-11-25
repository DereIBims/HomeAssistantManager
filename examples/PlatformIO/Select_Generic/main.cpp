#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");
// Select::Generic constructor: (manager, entity display name, list of selectable options)
HA::Select::Generic mode(&Manager, "Operating Mode", {"Auto", "Manual", "Off"});

void onModeCommand(const String &option) {
  Serial.print("Operating mode set to ");
  Serial.println(option);
  // setValue(confirmed option from the configured list)
  mode.setValue(option); // Confirm the option after the application accepts it.
}

void setup() {
  Serial.begin(115200);

  // setCommandCallback(function receiving the requested option as a const String &)
  mode.setCommandCallback(onModeCommand);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32 Select", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }

  // setValue(confirmed option from the configured list)
  mode.setValue("Auto");
}

void loop() {
  Manager.loop();
}
