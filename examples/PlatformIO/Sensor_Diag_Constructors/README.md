# Sensor Diagnostic Constructors Example

This example demonstrates the use of diagnostic sensors with both predefined and custom configurations. Diagnostic sensors are specifically designed for device diagnostics and system monitoring.

## Features

- Creates diagnostic sensors with both default and custom configurations
- Shows difference between predefined diagnostic classes and custom ones
- Demonstrates both numeric and text-based diagnostic sensors

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Diagnostic Sensors**: Creates two types of diagnostic sensors:
   - **Battery Level**: Uses predefined `HA::Battery` class with default unit (%)
   - **Custom Diagnostic**: Uses custom text-based diagnostic with no specific class/unit
3. **Value Updates**: Updates both sensors every 5 seconds
   - Battery: Numeric value (88%)
   - Custom Diag: Text state ("OK")

## Diagnostic vs Generic Sensors

Diagnostic sensors (`HA::Sensor::Diag`) are:
- Marked as diagnostic entities in Home Assistant
- Typically hidden from the main dashboard
- Used for system monitoring and troubleshooting
- Shown in the device's diagnostic section

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## Use Case

Perfect for:
- Device health monitoring
- System diagnostics
- Battery level reporting
- Custom status indicators
