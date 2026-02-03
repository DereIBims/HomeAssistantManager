# HASSDevice Library

A comprehensive Home Assistant MQTT device wrapper library for ESP32 microcontrollers with automatic discovery support.

## Features

- **Auto-Discovery**: Automatically registers devices with Home Assistant via MQTT discovery.
- **Device Classes**: Supports all major Home Assistant device classes including sensors, binary sensors, lights, switches, covers, and fans.
- **Hardware Integration**: Provides callbacks for physical hardware control without managing pins directly.
- **Device Grouping**: Groups all entities under a single HA device with shared metadata.
- **WiFi & MQTT Management**: Handles WiFi connection and MQTT communication.
- **Easy Configuration**: Simple constructors and setters for device setup.

## Supported Device Types

- **Sensors**: Temperature, humidity, illuminance, pressure, etc.
- **Binary Sensors**: Motion, door/window, presence, etc.
- **Lights**: On/off, brightness, RGB color control.
- **Switches**: Simple on/off switches.
- **Covers**: Blinds, curtains with position and state control.
- **Fans**: Speed and preset mode control.

## Dependencies

- [PubSubClient](https://github.com/knolleary/pubsubclient) (^2.8)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (^7.0)

## Installation

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps =
    https://github.com/yourusername/HASSDevice.git
```

### Manual

Copy the `HASSDevice` folder to your Arduino libraries directory.

## Usage

### Basic Setup

```cpp
#include <WiFi.h>
#include <HASSDevice.h>

// Option 1: Default constructor with setters
HASSDevice::HASSManager manager;
manager.setWifiCredentials("your-ssid", "your-password");
manager.setMqttServer("your-mqtt-server");
manager.setMqttPort(1883);
manager.setMqttCredentials("mqtt-user", "mqtt-password");
manager.setDeviceInfo("My ESP32 Device", "ESP32", "1.0.0");

// Option 2: MQTT-only constructor
HASSDevice::HASSManager manager("mqtt-server", 1883, "mqtt-user", "mqtt-password");
manager.setWifiCredentials("ssid", "password");

// Option 3: Full constructor (original)
HASSDevice::HASSManager manager("ssid", "password", "mqtt-server", 1883, "user", "pass", "Device Name");

void setup() {
    // Enable OTA updates (optional)
    manager.enableOTA("ota_password", "my-esp32-device");
    
    // Enable remote monitoring (optional)
    manager.enableRemoteLogging();  // Publish logs to MQTT
    manager.enableTelnet();         // Enable telnet server on port 23
    
    if (!manager.begin()) {
        Serial.println("Failed to connect to Home Assistant!");
        while (true) delay(1000);  // Halt
    }

    // Create devices
    auto sensor = new HASSDevice::Sensor(&manager, "Temperature", HASSDevice::SensorClass::Temperature);
    sensor->setState(23.5);
}
```

### Device Classes

Use the provided constants for device classes:

```cpp
// Sensors with default units
HASSDevice::Sensor temperature(&manager, "Temp", HASSDevice::SensorClass::Temperature); // °C
HASSDevice::Sensor humidity(&manager, "Humidity", HASSDevice::SensorClass::Humidity); // %
HASSDevice::Sensor battery(&manager, "Battery", HASSDevice::SensorClass::Battery); // %

// Binary Sensors
HASSDevice::BinarySensor motion(&manager, "Motion", HASSClass::Motion);

// Lights, Switches, Covers, Fans
HASSDevice::Light light(&manager, "Light");
HASSDevice::Switch switch(&manager, "Switch");
HASSDevice::Cover cover(&manager, "Cover");
HASSDevice::Fan fan(&manager, "Fan");
```

### Remote Monitoring

The library provides two ways to remotely monitor your ESP32 device:

#### MQTT Logging

Publish all log messages to MQTT topics for remote monitoring via Home Assistant or any MQTT client:

```cpp
// Enable MQTT logging (logs go to homeassistant/{deviceId}/logs)
manager.enableRemoteLogging();

// Or specify custom topic
manager.enableRemoteLogging("my/custom/logs/topic");

// Disable MQTT logging (back to serial only)
manager.disableRemoteLogging();
```

Log messages are published in real-time and can be monitored using:
- MQTT clients like MQTT Explorer
- Home Assistant MQTT integration
- Custom dashboards

#### Telnet Server

Access the device console remotely via telnet for debugging and monitoring:

```cpp
// Enable telnet server on default port 23
manager.enableTelnet();

// Or specify custom port
manager.enableTelnet(2323);

// Disable telnet server
manager.disableTelnet();
```

Connect using: `telnet <esp32-ip> [port]`

Available telnet commands:
- `help` - Show available commands
- `status` - Show device status
- `logs` - Show logging information
- `devices` - List all devices
- `wifi` - Show WiFi information
- `mqtt` - Show MQTT connection info
- `reboot` - Reboot the device
- `exit` - Disconnect from telnet

#### Mirroring Serial Output

To mirror `Serial.print()` and `Serial.println()` output to telnet clients:

```cpp
void loop() {
    // Your code...
    Serial.println("This goes to serial and telnet clients");
    
    // Or explicitly send to telnet only
    manager.sendToTelnet("This goes only to telnet clients");
}
```

**Note:** When remote logging is enabled, all ArduinoLog output is automatically published to MQTT. For Serial output, you need to use the `sendToTelnet()` method or modify your Serial.print calls.

## API Reference

### HASSManager

#### Constructors
- `HASSManager()` - Default constructor
- `HASSManager(String server, int port = 1883, String user = "", String pass = "")` - MQTT-only setup
- `HASSManager(String ssid, String pass, String server, int port = 1883, String user = "", String pass = "", String devName = "", String mf = "", String devId = "", String mdl = "", String sw = "", String sn = "")` - Full setup

#### WiFi Configuration
- `void setWifiCredentials(String ssid, String pass)`
- `void setWifiSSID(String ssid)`
- `void setWifiPassword(String pass)`

#### MQTT Configuration
- `void setMqttServer(String server)`
- `void setMqttPort(int port)`
- `void setMqttCredentials(String user, String pass)`
- `void setMqttUser(String user)`
- `void setMqttPassword(String pass)`

#### Device Information
- `void setDeviceInfo(String name, String manufacturer = "", String model = "", String swVersion = "", String serialNumber = "")`
- `void setDeviceName(String name)`
- `void setManufacturer(String mf)`
- `void setModel(String mdl)`
- `void setSwVersion(String sw)`
- `void setSerialNumber(String sn)`

#### OTA (Over-The-Air) Updates
- `void enableOTA(String password = "", String hostname = "")` - Enable OTA updates with optional password and hostname
- `void disableOTA()` - Disable OTA updates
- `void setOTAPassword(String password)` - Set OTA password for authentication
- `void setOTAHostname(String hostname)` - Set OTA hostname (defaults to device name)

#### Logging
- `void setLogLevel(int level)` - Set logging level (0=OFF, 1=FATAL, 2=ERROR, 3=WARNING, 4=INFO, 5=TRACE, 6=VERBOSE)
- `void enableVerboseLogging()` - Enable verbose logging (level 6)
- `void disableVerboseLogging()` - Disable verbose logging (level 4/INFO)

#### Remote Monitoring
- `void enableRemoteLogging(String mqttTopic = "")` - Enable MQTT-based logging. Logs are published to the specified MQTT topic (default: `homeassistant/{deviceId}/logs`)
- `void disableRemoteLogging()` - Disable MQTT logging and revert to serial-only output
- `void enableTelnet(int port = 23)` - Enable telnet server for remote access to device console
- `void disableTelnet()` - Disable telnet server
- `void sendToTelnet(String message)` - Send message to connected telnet clients
- `void sendToTelnet(const char* message)` - Send C-string message to connected telnet clients

#### Connection Management
- `bool begin()` - Initialize WiFi, MQTT, and OTA connections. Returns true on success, false if configuration is incomplete.
- `void loop()` - Maintain connection, handle MQTT messages, and process OTA updates

**Note:** `begin()` validates that WiFi SSID/password and MQTT server/port are configured before attempting connection. If any required settings are missing, it prints an error message and returns false.

### Device Classes

#### Sensor
- `Sensor(HASSManager* mgr, String name, String devClass = "", String unit = "")` - Basic constructor
- `Sensor(HASSManager* mgr, String name, SensorClass sensorClass)` - Constructor with default unit
- `void setValue(float value)` - Set sensor value
- `void setUnit(String unit)` - Set unit of measurement

#### Other Devices

All devices inherit from `HASSDevice` and support:
- `setState(...)` - Update device state
- `setCommandCallback(std::function<void(HASSCommand)>)` - Handle commands from HA

## License

MIT License - see LICENSE file for details.

## Contributing

Contributions welcome! Please open issues and pull requests on GitHub.