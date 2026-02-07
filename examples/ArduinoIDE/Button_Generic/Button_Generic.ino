#include <HomeAssistantManager.h>

// Manager constructor: (ssid, password, mqttHost)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Button::Generic constructor: (manager, name)
HA::Button::Generic testButton(&Manager, "Test Button");

void onButtonPress() {
  Serial.println("Button pressed from Home Assistant");
}

void setup() {
  Serial.begin(115200);
  testButton.setCommandCallback(onButtonPress);

  if (!Manager.begin("ESP32_Button", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
}
