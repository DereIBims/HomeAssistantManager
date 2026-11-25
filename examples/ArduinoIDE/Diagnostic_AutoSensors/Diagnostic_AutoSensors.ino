#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Sensor::Diag::AutoRSSI constructor: (manager, entity display name)
HA::Sensor::Diag::AutoRSSI rssi(&Manager, "RSSI");
// Sensor::Diag::AutoUptime constructor: (manager, entity display name)
HA::Sensor::Diag::AutoUptime uptime(&Manager, "Uptime");
// Sensor::Diag::AutoFreeHeap constructor: (manager, entity display name)
HA::Sensor::Diag::AutoFreeHeap heap(&Manager, "Free Heap");
// Sensor::Diag::AutoResetReason constructor: (manager, entity display name)
HA::Sensor::Diag::AutoResetReason resetReason(&Manager, "Reset Reason");

void setup() {
  Serial.begin(115200);
  // setAutoDiagInterval(update interval in milliseconds)
  Manager.setAutoDiagInterval(15000);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32_AutoDiag", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  delay(100);
}
