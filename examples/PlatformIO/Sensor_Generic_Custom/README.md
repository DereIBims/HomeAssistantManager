# Sensor Generic - Custom Class and Unit Example

This example shows how to create a sensor with a custom device class and custom unit of measurement that is not predefined in the library.

## Features

- Creates a wind speed sensor with custom class and unit
- Demonstrates flexibility of the library for non-standard sensors
- Updates sensor value every 5 seconds

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Custom Sensor Creation**: Creates a wind speed sensor with:
   - Name: "Wind Speed"
   - Device Class: `"speed"` (custom string)
   - Unit: `"m/s"` (custom unit string)
   - State Class: `HA::MEASUREMENT`
3. **Value Updates**: Sets wind speed to 6.42 m/s with 2 decimal precision every 5 seconds

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## Use Case

Perfect for:
- Creating sensors for non-standard measurements
- Using custom device classes not predefined in Home Assistant
- Defining your own units of measurement
- Advanced sensor customization
