#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Auto-diagnostic constructors: (manager, name)
HA::Sensor::Diag::AutoRSSI rssi(&Manager, "RSSI");
HA::Sensor::Diag::AutoUptime uptime(&Manager, "Uptime");
HA::Sensor::Diag::AutoFreeHeap heap(&Manager, "Free Heap");
HA::Sensor::Diag::AutoResetReason resetReason(&Manager, "Reset Reason");

void setup() {
  Serial.begin(115200);
  Manager.setAutoDiagInterval(15000);

  if (!Manager.begin("ESP32_AutoDiag", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
  // Auto-diagnostic sensors update automatically in Manager.loop()
  // No additional delay needed
}
