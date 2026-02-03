#include <Devices/Button.h>
#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Button::Restart constructor: (manager, name)
HA::Button::Restart restartButton(&Manager, "Restart Device");

void setup() {
  Serial.begin(115200);
  if (!Manager.begin("ESP32_Restart", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
}
