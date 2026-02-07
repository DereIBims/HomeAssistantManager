# Switch Outlet Example

This example demonstrates how to create a specialized outlet switch entity in Home Assistant for controlling power outlets and similar appliances.

## Features

- Creates an outlet-class switch entity in Home Assistant
- Specialized device class for power outlets and appliances
- Receives commands from Home Assistant to control the outlet
- Can programmatically update the outlet state from the ESP32
- Shows proper outlet feedback and state management
- Bidirectional communication (HA ↔ ESP32)

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Outlet Creation**: Creates an outlet-class switch with:
   - Name: "Power Outlet"
   - Device Class: "outlet"
   - Callback function: `onOutletCommand()`
3. **Command Handling**: When the outlet is toggled in Home Assistant, `onOutletCommand()` executes
4. **Relay Control**: Controls a relay or GPIO pin to toggle power to the outlet
5. **State Feedback**: Updates Home Assistant with the actual outlet state

## Outlet vs Generic Switch

- **Generic Switch**: General-purpose ON/OFF control, appears as a toggle
- **Outlet Switch**: Specialized for power outlets/appliances, has specific Home Assistant integrations and automations

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname
- `RELAY_PIN` - The GPIO pin connected to your relay (uncomment and set as needed)
- `RELAY_FEEDBACK_PIN` - Optional pin for reading outlet status (uncomment and set as needed)

## GPIO Setup (Example)

```cpp
#define RELAY_PIN 12
#define RELAY_FEEDBACK_PIN 13

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_FEEDBACK_PIN, INPUT);
  // ... rest of setup
}
```

## API

### Constructor
```cpp
HA::Switch::Outlet(Manager *manager, const char *name)
```

### Methods
- `void setCommandCallback(Callback cb)` - Set callback function for state changes from Home Assistant
- `void setValue(bool state)` - Update outlet state (true = ON, false = OFF)

## Manager Constructor Parameter

The Manager constructor now supports device cleanup:
```cpp
bool begin(const char *deviceName, const char *manufacturer, const char *model, 
           const char *swVersion, bool unregisterDevices = false)
```

- **unregisterDevices**: Set to `true` to unregister the entire device from MQTT on connect. Useful for device cleanup when removing from Home Assistant.

## ⚠️ Critical Notes About Device Removal

If you set `unregisterDevices = true`:
- ⚠️ **Only entities defined in THIS code are removed** - old/renamed entities stay in Home Assistant
- ⚠️ **Program halts after removal** - the device stops all activity (intentional)
- ⚠️ **Must change back to `false` and reflash** to use the device again
- See the `Device_Removal` example for complete removal workflow

## Use Cases

Perfect for:
- Smart power outlets and extension cords
- Controllable appliances (fans, pumps, heaters)
- Power distribution units
- Device with power feedback/monitoring
- Any specialized power control scenario
- Integration with power monitoring systems

## Safety Considerations

When controlling high-power devices:
- Use appropriate relay ratings for your load
- Include proper fusing for circuit protection
- Verify relay feedback before attempting to control
- Consider adding current sensing for safety
- Test thoroughly before deploying in production
