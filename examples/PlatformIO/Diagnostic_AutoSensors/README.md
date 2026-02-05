# Diagnostic Auto Sensors Example

This example demonstrates the automatic diagnostic sensors that continuously monitor ESP32 system metrics without requiring manual updates.

## Features

- Automatic WiFi signal strength (RSSI) monitoring
- Automatic uptime tracking
- Automatic free heap memory monitoring
- Automatic reset reason reporting
- Configurable update interval for all auto-sensors

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Auto Update Interval**: Sets diagnostic update interval to 15 seconds (15000ms)
3. **Auto Sensors**: Creates four automatic diagnostic sensors:
   - **RSSI**: Reports WiFi signal strength in dBm
   - **Uptime**: Reports device uptime since last restart
   - **Free Heap**: Reports available heap memory in bytes
   - **Reset Reason**: Reports why the device was last reset/restarted
4. **Automatic Updates**: All sensors update automatically at the specified interval - no manual code needed!

## Available Auto Sensors

- `HA::Sensor::Diag::AutoRSSI` - WiFi signal strength
- `HA::Sensor::Diag::AutoUptime` - Device uptime
- `HA::Sensor::Diag::AutoFreeHeap` - Free heap memory
- `HA::Sensor::Diag::AutoResetReason` - Last reset reason

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

You can also adjust:
- `setAutoDiagInterval(15000)` - Change the update interval (in milliseconds)

## Use Case

Perfect for:
- Easy device monitoring without writing update code
- Tracking ESP32 health metrics
- Diagnosing connectivity issues
- Memory leak detection
- Understanding device reset patterns
