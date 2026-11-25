#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Button::Generic constructor: (manager, entity display name, diagnostic category = false)
HA::Button::Generic testButton(&Manager, "Test Button");

void onButtonPress() {
  Serial.println("Button pressed from Home Assistant");
}

void setup() {
  Serial.begin(115200);
  // setCommandCallback(function called on button press, with no arguments)
  testButton.setCommandCallback(onButtonPress);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32_Button", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  Manager.loop();
}
