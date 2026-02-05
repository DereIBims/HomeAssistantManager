# Button Generic Example

This example demonstrates how to create a button in Home Assistant that triggers a callback function on your ESP32 when pressed.

## Features

- Creates a button entity in Home Assistant
- Executes custom callback when button is pressed from HA
- Shows bidirectional communication (HA → ESP32)

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Button Creation**: Creates a button with:
   - Name: "Test Button"
   - Callback function: `onButtonPress()`
3. **Callback Function**: When the button is pressed in Home Assistant, the `onButtonPress()` function executes
4. **Action**: Prints a message to Serial when triggered

## Key Concepts

- Buttons in Home Assistant are **action triggers** - they don't have a state
- They're **one-way**: Home Assistant sends command to ESP32
- Perfect for triggering actions on your device remotely
- Callback function can perform any action you need

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## Use Case

Perfect for:
- Remote triggering of device actions
- Running calibration routines
- Manual data updates
- Testing device functionality
- Triggering custom events
