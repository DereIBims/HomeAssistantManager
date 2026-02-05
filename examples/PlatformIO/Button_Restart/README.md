# Button Restart Example

This example shows how to create a special restart button that allows you to remotely restart your ESP32 device from Home Assistant.

## Features

- Creates a dedicated restart button in Home Assistant
- Automatically restarts ESP32 when pressed
- Built-in functionality - no callback needed

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Restart Button**: Creates a special button with:
   - Name: "Restart Device"
   - Built-in restart functionality
3. **Auto Restart**: When pressed in Home Assistant, the ESP32 automatically restarts

## Key Concepts

- `HA::Button::Restart` is a **specialized button** type
- No callback function needed - restart is handled automatically
- The device will:
  1. Receive the restart command via MQTT
  2. Close connections gracefully
  3. Perform ESP.restart()
- Device will reconnect to WiFi and MQTT after restart

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## Use Case

Perfect for:
- Remote device management
- Recovering from stuck states
- Applying configuration changes that require restart
- Troubleshooting without physical access
- Convenience in home automation setups
