#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Outlet is a specialized switch with outlet device class
// Switch::Outlet constructor: (manager, entity display name)
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
  
  // setCommandCallback(function receiving the requested on/off state as a bool)
  powerOutlet.setCommandCallback(onOutletCommand);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
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
    // setValue(switch state, true = on and false = off)
    // powerOutlet.setValue(currentState);
    lastCheck = millis();
  }
}
