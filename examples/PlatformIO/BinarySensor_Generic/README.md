# Binary Sensor Generic Example

This example demonstrates how to create a binary sensor that reports ON/OFF states to Home Assistant.

## Features

- Creates a door binary sensor
- Automatically toggles state every 3 seconds for demonstration
- Shows proper binary sensor state management

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Binary Sensor Creation**: Creates a door sensor with:
   - Name: "Door"
   - Device Class: `HA::Door`
   - States: true (open) / false (closed)
3. **State Updates**: Toggles door state every 3 seconds using millis() timing

## Binary Sensor Types

The library supports various binary sensor device classes:
- `HA::Door` - Door sensors
- `HA::Motion` - Motion/occupancy sensors
- `HA::Window` - Window sensors
- And many more predefined classes

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## Use Case

Perfect for:
- Door/window sensors
- Motion detectors
- Any ON/OFF state monitoring
- Contact sensors
- Occupancy detection
