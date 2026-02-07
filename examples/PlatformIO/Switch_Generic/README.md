# Switch Generic Example

This example demonstrates how to create a switch entity in Home Assistant that can be controlled bidirectionally with your ESP32.

## Features

- Creates a switch entity in Home Assistant
- Receives commands from Home Assistant to toggle the switch
- Can programmatically update the switch state from the ESP32
- Executes callback function when switch is toggled from HA
- Shows bidirectional communication (HA ↔ ESP32)

## How It Works

1. **Manager Setup**: Initializes the HomeAssistantManager with WiFi and MQTT credentials
2. **Switch Creation**: Creates a generic switch with:
   - Name: "Main Switch"
   - Callback function: `onSwitchCommand()`
3. **Callback Function**: When the switch is toggled in Home Assistant, the `onSwitchCommand()` function executes with the new state
4. **Action**: You can control relays, LEDs, or any other device based on the switch state
5. **State Synchronization**: The switch state is kept in sync between Home Assistant and the device

## Key Concepts

- Switches in Home Assistant are **controllable entities** with ON/OFF states
- They're **bidirectional**: Home Assistant ↔ ESP32 can both send and receive state
- Use for: Lights, relays, power outlets, pumps, fans, etc.
- The callback is triggered when state changes from Home Assistant
- Use `setValue()` to update state from the device itself

## Configuration

Before using this example, update the following values:
- `"your-ssid"` - Your WiFi network name
- `"your-password"` - Your WiFi password
- `"mqtt-host"` - Your MQTT broker IP address or hostname

## API

### Constructor
```cpp
HA::Switch::Generic(Manager *manager, const char *name)
```

### Methods
- `void setCommandCallback(Callback cb)` - Set callback function for state changes from Home Assistant
- `void setValue(bool state)` - Update switch state (true = ON, false = OFF)

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
- Light switches
- Power outlets and appliances
- Pump or fan control
- GPIO relay control
- Remote device toggling
- Any binary ON/OFF control element
