# Advanced Multi-Entity with Timers Example

This comprehensive example demonstrates a complete multi-entity setup using various device types with timer-based updates, showing real-world usage patterns.

## Features

- Multiple entity types in one project
- Timer-based non-blocking updates
- MQTT authentication
- Auto-diagnostic sensors
- Mixed sensor types (default and custom units)
- Binary sensor state management
- Button with callback

## Entities Included

1. **Temperature Sensor** - Generic sensor with default unit (°C)
2. **Custom Power Sensor** - Generic sensor with custom unit (W)
3. **Motion Sensor** - Binary sensor for motion detection
4. **Test Button** - Interactive button with callback

Plus automatic diagnostic sensors (RSSI, uptime, heap, reset reason) updated every 20 seconds.

## How It Works

1. **Advanced Manager Setup**:
   - WiFi and MQTT broker configuration
   - MQTT port set to 1883
   - MQTT authentication with username/password
   - Auto-diagnostic interval set to 20 seconds
   - Log level set to INFO

2. **Timer-Based Updates**:
   - **Sensor Updates**: Every 5 seconds
     - Temperature: 22.5°C
     - Power: 123.4W
   - **Motion Toggle**: Every 3 seconds
     - Alternates between detected/clear
   - **Diagnostics**: Every 20 seconds (automatic)

3. **Non-Blocking Design**: Uses `millis()` for timing to keep loop responsive

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname
- `"mqtt-user"` - Your MQTT username (if authentication enabled)
- `"mqtt-pass"` - Your MQTT password (if authentication enabled)

You can also adjust:
- `setMqttPort(1883)` - Change MQTT port if needed
- `setAutoDiagInterval(20000)` - Adjust diagnostic update interval
- Timer intervals for sensors and motion

## Use Case

Perfect for:
- Real-world multi-sensor projects
- Learning best practices for entity management
- Non-blocking timer-based updates
- Projects requiring multiple entity types
- Understanding complete device integration
- Production-ready code patterns
