#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost, logLevel)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Switch::Outlet constructor: (manager, name)
// Outlet is a specialized switch with outlet device class
HA::Switch::Outlet powerOutlet(&Manager, "Power Outlet");

void onOutletCommand(bool state) {
  Serial.print("Outlet command received: ");
  Serial.println(state ? "ON" : "OFF");
  
  // Control the outlet relay
  // digitalWrite(RELAY_PIN, state ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  
  // Setup GPIO for relay (if needed)
  // pinMode(RELAY_PIN, OUTPUT);
  
  powerOutlet.setCommandCallback(onOutletCommand);

  // begin(deviceName, manufacturer, model, softwareVersion, unregisterDevices = false)
  // unregisterDevices: Set to true to unregister the entire device from MQTT on connect
  // ⚠️ CRITICAL: Setting to true will remove ONLY entities in THIS code, halt the program,
  // and require changing back to false to reactivate. See Device_Removal example.
  if (!Manager.begin("ESP32_Outlet", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  
  // Example: Check actual outlet state and update
  // This could read from a current sensor or relay feedback pin
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 5000) {
    // bool currentState = digitalRead(RELAY_FEEDBACK_PIN);
    // powerOutlet.setValue(currentState);
    lastCheck = millis();
  }
}
