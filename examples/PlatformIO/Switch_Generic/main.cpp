#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost, logLevel)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Switch::Generic constructor: (manager, name)
HA::Switch::Generic mainSwitch(&Manager, "Main Switch");

void onSwitchCommand(bool state) {
  Serial.print("Switch command received: ");
  Serial.println(state ? "ON" : "OFF");
  
  // Perform your action here
  // For example, toggle a relay or LED
}

void setup() {
  Serial.begin(115200);
  mainSwitch.setCommandCallback(onSwitchCommand);

  // begin(deviceName, manufacturer, model, softwareVersion, unregisterDevices = false)
  // unregisterDevices: Set to true to unregister the entire device from MQTT on connect
  // ⚠️ CRITICAL: Setting to true will remove ONLY entities in THIS code, halt the program,
  // and require changing back to false to reactivate. See Device_Removal example.
  if (!Manager.begin("ESP32_Switch", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  
  // Example: Toggle switch state every 10 seconds
  static unsigned long lastToggle = 0;
  if (millis() - lastToggle > 10000) {
    static bool state = false;
    mainSwitch.setValue(state);
    state = !state;
    lastToggle = millis();
  }
}
