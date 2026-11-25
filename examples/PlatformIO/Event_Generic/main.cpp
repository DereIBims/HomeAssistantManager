#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");
// Event::Generic constructor: (manager, entity display name, list of event types, Home Assistant event device class)
HA::Event::Generic doorbell(&Manager, "Doorbell", {"press", "hold"}, "doorbell");

void setup() {
  Serial.begin(115200);

  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  if (!Manager.begin("ESP32 Event", "MyCompany", "ESP32", "1.0.0")) {
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Send p for press or h for hold in the serial monitor.");
}

void loop() {
  Manager.loop();
  int input = Serial.read();
  if (input == 'p') {
    // trigger(event type from the configured list)
    doorbell.trigger("press");
  }
  else if (input == 'h') {
    // trigger(event type from the configured list)
    doorbell.trigger("hold");
  }
}
