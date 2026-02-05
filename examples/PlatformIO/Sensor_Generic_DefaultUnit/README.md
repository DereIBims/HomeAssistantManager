# Sensor Generic - Default Unit Example

This example demonstrates how to create a basic sensor using the HomeAssistantManager library with a predefined sensor class and its default unit of measurement.

## Features

- Creates a temperature sensor using the built-in `HA::Temperature` class
- Uses the default unit of measurement (°C for temperature)
- Updates sensor value every 5 seconds
- Demonstrates basic Manager initialization with WiFi and MQTT settings

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi credentials, MQTT broker, and log level
2. **Sensor Creation**: Creates a temperature sensor with:
   - Name: "Temperature"
   - Device Class: `HA::Temperature` (predefined class)
   - State Class: `HA::MEASUREMENT`
   - Default unit: °C (automatically set by the Temperature class)
3. **Value Updates**: Sets temperature value to 23.7°C with 1 decimal precision every 5 seconds

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## Use Case

Perfect for:
- Getting started with the library
- Creating sensors with standard units (temperature, humidity, pressure, etc.)
- Learning the basic sensor API
