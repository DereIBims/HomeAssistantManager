# HomeAssistantManager (ESP32)

Home Assistant MQTT auto-discovery library for ESP32. It provides a small set of entity types (sensor, binary sensor, button) with simple APIs and diagnostic helpers.

## Features

- **Auto-Discovery**: Registers entities via Home Assistant MQTT discovery topics.
- **Device Grouping**: All entities share a single HA device (same identifiers + metadata).
- **Diagnostics**: Built-in auto-updated sensors for RSSI, uptime, free heap, and reset reason.
- **Command Callbacks**: Button entities can trigger callbacks from Home Assistant.
- **ESP32-only**: Uses ESP32 WiFi and reset APIs.

## Supported Entity Types

- **Sensor**: `HA::Sensor::Generic`, `HA::Sensor::Diag`, plus auto-diagnostic sensor variants.
- **Binary Sensor**: `HA::BinarySensor::Generic`.
- **Button**: `HA::Button::Generic`, `HA::Button::Restart`.

## Dependencies

- [PubSubClient](https://github.com/knolleary/pubsubclient) (^2.8)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (^7.0)
- [ArduinoLog](https://github.com/thijse/ArduinoLog) (^1.0.1)

## Installation (PlatformIO)

Add to your [platformio.ini](platformio.ini):

```ini
lib_deps =
        https://github.com/DereIBims/HomeAssistantManager.git
```

## Quick Start

```cpp
#include "HomeAssistantManager.h"

// Manager requires WiFi + MQTT server, log level is optional
HA::Manager hassManager("your-ssid", "your-password", "mqtt-host", LOG_LEVEL_INFO);

// Optional MQTT settings
// hassManager.setMqttPort(1883);
// hassManager.setMqttCredentials("mqtt-user", "mqtt-pass");

// Example entities
HA::Sensor::Generic tempSensor(&hassManager, "Temperature", HA::Temperature, HA::MEASUREMENT);
HA::BinarySensor::Generic doorSensor(&hassManager, "Door", HA::Door);
HA::Button::Generic testButton(&hassManager, "Test Button");

void onTestButton() {
    Serial.println("Button pressed");
}

void setup() {
    Serial.begin(115200);

    testButton.setCommandCallback(onTestButton);

    if (!hassManager.begin("ESP32_HASS", "MyCompany", "ESP32", "1.0.0")) {
        while (true) {
            delay(1000);
        }
    }
}

void loop() {
    hassManager.loop();
    tempSensor.setValue(23.5, 1);
    doorSensor.setValue(true);
    delay(5000);
}
```

## Diagnostic Sensors

These update automatically in `Manager::loop()`:

```cpp
HA::Sensor::Diag::AutoRSSI rssi(&hassManager, "RSSI");
HA::Sensor::Diag::AutoUptime uptime(&hassManager, "Uptime");
HA::Sensor::Diag::AutoFreeHeap heap(&hassManager, "Free Heap");
HA::Sensor::Diag::AutoResetReason resetReason(&hassManager, "Reset Reason");
```

## Examples

Comprehensive examples are provided for each device type and constructor variation.

**PlatformIO:** Examples with `main.cpp` structure.
- `Sensor_Generic_DefaultUnit` - Temperature sensor with predefined unit
- `Sensor_Generic_Custom` - Custom sensor with arbitrary class and unit
- `Sensor_Diag_Constructors` - Diagnostic sensor constructors
- `Diagnostic_AutoSensors` - Auto-updated diagnostic sensors (RSSI, uptime, heap, reset reason)
- `BinarySensor_Generic` - Door/window binary sensor example
- `Button_Generic` - Button with callback
- `Button_Restart` - Restart button
- `Advanced_MultiEntity_With_Timers` - Multiple entities with timing logic

**Arduino IDE:** Same examples as standalone `.ino` files.

All examples include detailed constructor comments and cover all available APIs.

## API Reference (Current)

### Manager

- `Manager(const char *ssid, const char *pass, const char *mqttServer, int logLevel = LOG_LEVEL_INFO)`
- `void setMqttPort(uint16_t port)`
- `void setMqttCredentials(const char *user, const char *pass)`
- `void setAutoDiagInterval(unsigned long intervalMs)`
- `bool begin(const char *deviceName, const char *manufacturer, const char *model, const char *swVersion)`
- `void loop()`

### Sensor

- `Sensor::Generic(Manager *mgr, const char *name, SensorClass sensorClass, const char *stateClass = HA::MEASUREMENT)`
- `Sensor::Generic(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *stateClass = HA::MEASUREMENT)`
- `void setValue(float value, int decimalPlaces = 1)`
- `void setValue(int value)`
- `void setValue(long value)`
- `void setValue(double value, int decimalPlaces = 1)`

### Binary Sensor

- `BinarySensor::Generic(Manager *mgr, const char *name, const char *sensorClass)`
- `void setValue(bool state)`

### Button

- `Button::Generic(Manager *mgr, const char *name)`
- `Button::Restart(Manager *mgr, const char *name)`
- `void setCommandCallback(Callback cb)`

## Notes

- ESP32 only (guarded by `ARDUINO_ARCH_ESP32`).
- Entity names are used in MQTT topics and unique IDs, and are combined with the device MAC.
- Only the entity types listed above are implemented in this library.
- AI assistance note: AI was used to generate documentation and examples and to answer occasional questions. It was not used for “vibe coding.” All library code is handwritten.

## License

MIT License - see LICENSE file for details.