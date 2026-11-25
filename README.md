# HomeAssistantManager (ESP32)

Home Assistant MQTT auto-discovery library for ESP32. It supports sensors, binary sensors, buttons, switches, numbers, selects, and events, with simple APIs and diagnostic helpers.

## Features

- **Auto-Discovery**: Registers entities via Home Assistant MQTT discovery topics.
- **Device Grouping**: All entities share a single HA device (same identifiers + metadata).
- **Diagnostics**: Built-in auto-updated sensors for RSSI, uptime, free heap, and reset reason.
- **Command Callbacks**: Buttons, switches, numbers, and selects can receive commands from Home Assistant.
- **ESP32-only**: Uses ESP32 WiFi and reset APIs.

## Supported Entity Types

- **Sensor**: `HA::Sensor::Generic`, `HA::Sensor::Diag`, plus auto-diagnostic sensor variants.
- **Binary Sensor**: `HA::BinarySensor::Generic`.
- **Button**: `HA::Button::Generic`, `HA::Button::Restart`.
- **Switch**: `HA::Switch::Generic`, `HA::Switch::Outlet`.
- **Number**: `HA::Number::Generic`.
- **Select**: `HA::Select::Generic`.
- **Event**: `HA::Event::Generic`.

## Dependencies

- [PubSubClient](https://github.com/knolleary/pubsubclient) (^2.8)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (^7.0)
- [ArduinoLog](https://github.com/thijse/ArduinoLog) (^1.0.1)

## Installation (PlatformIO)

Add to your `platformio.ini`:

```ini
lib_deps =
        dereibims/HomeAssistantManager@^1.1.4
        knolleary/PubSubClient@^2.8
        bblanchon/ArduinoJson@^7.0
        thijse/ArduinoLog@^1.0.1
```

**Note:** All dependencies are automatically handled by the library definition, however for some reason they're not available for the project. Therefor they need to be added to `lib_deps`.

## Installation (Arduino IDE)

1. Download the source code from the [latest release on GitHub](https://github.com/DereIBims/HomeAssistantManager/releases)
2. In Arduino IDE, go to **Sketch** → **Include Library** → **Add .ZIP Library**
3. Select the downloaded `.zip` file

**⚠️ Important:** You must manually install all dependencies - they will NOT be installed automatically:

- [PubSubClient by Nick O'Leary](https://www.arduino.cc/reference/en/libraries/pubsubclient/)
- [ArduinoJson by Benoit Blanchon](https://www.arduino.cc/reference/en/libraries/arduinojson/)
- [ArduinoLog by Thijs Elenbaas](https://www.arduino.cc/reference/en/libraries/arduinolog/)

Install each dependency through **Sketch** → **Include Library** → **Manage Libraries**, then search and install each one.

## Quick Start

```cpp
#include "HomeAssistantManager.h"

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager hassManager("your-ssid", "your-password", "mqtt-host", LOG_LEVEL_INFO);

// setMqttPort(MQTT broker TCP port)
// hassManager.setMqttPort(1883);
// setMqttCredentials(MQTT username, MQTT password)
// hassManager.setMqttCredentials("mqtt-user", "mqtt-pass");

// Sensor::Generic constructor: (manager, entity display name, sensor preset with default unit, state class)
HA::Sensor::Generic tempSensor(&hassManager, "Temperature", HA::Temperature, HA::MEASUREMENT);
// BinarySensor::Generic constructor: (manager, entity display name, Home Assistant binary sensor device class)
HA::BinarySensor::Generic doorSensor(&hassManager, "Door", HA::Door);
// Button::Generic constructor: (manager, entity display name, diagnostic category = false)
HA::Button::Generic testButton(&hassManager, "Test Button");

void onTestButton() {
    Serial.println("Button pressed");
}

void setup() {
    Serial.begin(115200);

    // setCommandCallback(function called on button press, with no arguments)
    testButton.setCommandCallback(onTestButton);

    // begin(device name, manufacturer, model, firmware version, unregister entities = false)
    if (!hassManager.begin("ESP32_HASS", "MyCompany", "ESP32", "1.0.0")) {
        while (true) {
            delay(1000);
        }
    }
}

void loop() {
    hassManager.loop();
    // setValue(measured value, number of decimal places)
    tempSensor.setValue(23.5, 1);
    // setValue(door state, true = open and false = closed)
    doorSensor.setValue(true);
    delay(5000);
}
```

## Diagnostic Sensors

These update automatically in `Manager::loop()`:

```cpp
// Auto-diagnostic constructors: (manager, entity display name)
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
- `Switch_Generic` - Generic switch with bidirectional control
- `Switch_Outlet` - Outlet-class switch for power outlets and appliances
- `Number_Generic` - Adjustable numeric value with a typed command callback
- `Select_Generic` - Operating mode selected from a list of options
- `Event_Generic` - Doorbell events triggered from the serial monitor
- `Device_Removal` - Demonstrates how to cleanly remove a device from Home Assistant
- `Advanced_MultiEntity_With_Timers` - Multiple entities with timing logic

**Arduino IDE:** Same examples as standalone `.ino` files.

The examples show how to construct entities and register callbacks.

## API Reference (Current)

### Manager

- `Manager(const char *ssid, const char *pass, const char *mqttServer, int logLevel = LOG_LEVEL_INFO)`
- `void setMqttPort(uint16_t port)`
- `void setMqttCredentials(const char *user, const char *pass)`
- `void setAutoDiagInterval(unsigned long intervalMs)`
- `bool begin(const char *deviceName, const char *manufacturer, const char *model, const char *swVersion, bool unregisterDevices = false)`
  - **unregisterDevices parameter:**
    - `false` (default): Normal operation - device registers and stays registered
    - `true`: ⚠️ **Removes ONLY entities defined in current code, program halts after removal, must set to `false` to reactivate**
    - **Important**: Old/renamed entities not in current code are NOT removed (delete manually from Home Assistant or the MQTT Broker with something like MQTT Explorer)
    - See `Device_Removal` example for complete workflow
- `void loop()`

### Sensor

- `Sensor::Generic(Manager *mgr, const char *name, SensorClass sensorClass, const char *stateClass = HA::MEASUREMENT)`
- `Sensor::Generic(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *stateClass = HA::MEASUREMENT)`
- `void setValue(float value, int decimalPlaces = 1)`
- `void setValue(int value)`
- `void setValue(long value)`
- `void setValue(double value, int decimalPlaces = 1)`

Energy (`HA::Energy`) and volume (`HA::Volume`) use `HA::TOTAL` when the default measurement state class is supplied. For a meter that only increases between resets, pass `HA::TOTAL_INCREASING` explicitly.

```cpp
// Sensor::Generic constructor: (manager, entity display name, sensor preset with default unit, state class)
HA::Sensor::Generic energy(&hassManager, "Energy", HA::Energy, HA::TOTAL_INCREASING);
```

### Binary Sensor

- `BinarySensor::Generic(Manager *mgr, const char *name, const char *sensorClass)`
- `void setValue(bool state)`

### Button

- `Button::Generic(Manager *mgr, const char *name)`
- `Button::Restart(Manager *mgr, const char *name)`
- `void setCommandCallback(Callback cb)` registers a callback for the `PRESS` command.

### Switch

- `Switch::Generic(Manager *mgr, const char *name)`
- `Switch::Outlet(Manager *mgr, const char *name)`
- `void setCommandCallback(Callback cb)`
- `void setValue(bool state)`

### Number

- `Number::Generic(Manager *mgr, const char *name, float min, float max, float step = 1, const char *unit = nullptr)`
- `void setCommandCallback(Callback cb)` accepts a callback taking a `float`.
- `bool setValue(float value)` publishes the confirmed value as retained MQTT state.

Use finite bounds with `min < max` and a step of at least `0.001`. An invalid configuration is skipped. Home Assistant uses the step in its UI. The library checks that received and published values are within the configured bounds.

### Select

- `Select::Generic(Manager *mgr, const char *name, std::initializer_list<const char *> options)`
- `void setCommandCallback(Callback cb)` accepts a callback taking a `const String &`.
- `bool setValue(const String &value)` publishes a configured option as retained MQTT state.

Provide distinct nonempty options. MQTT reserves `None` to reset the state. For Number and Select, call `setValue()` when your sketch accepts a command or changes the value locally.

### Event

- `Event::Generic(Manager *mgr, const char *name, std::initializer_list<const char *> eventTypes, const char *deviceClass = nullptr)`
- `bool trigger(const String &eventType)` publishes one of the configured event types without retaining it.

Provide at least one event type. Event reports occurrences such as a physical button press from the ESP32 to Home Assistant.

## Notes

- ESP32 only (guarded by `ARDUINO_ARCH_ESP32`).
- By default, entity names and the device MAC form the unique ID. Characters outside `A-Z`, `a-z`, `0-9`, `_` and `-` are replaced with underscores in generated topics.
- For new entities, call `entity.setEntityId("stable_id")` before `Manager::begin()` to keep the MQTT topics and unique ID stable when the display name changes. Use distinct IDs within each entity type, especially when two names normalize to the same topic. Adding an explicit ID to an existing entity can change its Home Assistant identity.
- **Device Removal**: When `unregisterDevices = true` in `Manager::begin()`:
  - ⚠️ Only removes entities **currently defined in your code**
  - ⚠️ Program **halts after removal** (intentional - no entities to process)
  - ⚠️ **Must set back to `false` and reflash to use device again**
  - Old/renamed entities must be manually deleted from Home Assistant
  - See `Device_Removal` example for the complete workflow.
- AI assistance note: The original library implementation was written by hand. AI was used for documentation, examples, and later maintenance and entity additions.

## License

MIT License - see LICENSE file for details.