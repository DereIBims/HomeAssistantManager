# Device Removal Example

This example demonstrates how to completely remove a device from Home Assistant MQTT.

## Features

- Shows how to use the `unregisterDevices` parameter
- Explains the device removal workflow
- Demonstrates proper cleanup procedure

## ⚠️ CRITICAL: What Gets Removed

**ONLY entities explicitly created in your code are removed.**

- **Will be removed**: Any entity created with `new HA::Sensor::Generic(...)`, `new HA::Button::Generic(...)`, etc. in your current code
- **Will NOT be removed**: Previously created entities that were renamed, deleted from code, or added in older code versions
- **Orphaned entities**: If you previously had an entity called "Old Sensor" and now have "New Sensor", only "New Sensor" is removed. "Old Sensor" stays in Home Assistant

### ⚠️ CRITICAL: Program Halts After Removal

**The program STOPS after removal - there is nothing left for it to do.** This is intentional behavior:
- No entities exist to monitor
- No values are being sent
- The device has no purpose

## When to Use Device Removal

Use device removal when you need to:
- **Permanently retire** a device from Home Assistant
- **Clean up** only the entities currently in your code from this specific device
- **Replace** an ESP32 with a completely new device in the same network
- **Migrate** a device to a new project or network

**NOT suitable for:**
- Removing old/orphaned entities - manually delete them in Home Assistant instead
- Updating entity names - edit your code and reflash with `false`, old names remain until manually deleted

## How It Works

The `unregisterDevices` parameter in the `Manager::begin()` method controls device registration:

```cpp
bool begin(const char *deviceName, const char *manufacturer, const char *model, 
           const char *swVersion, bool unregisterDevices = false)
```

- **false (default)**: Normal operation - device registers and stays registered
- **true**: Device unregisters from MQTT and Home Assistant will remove it

## Device Removal Workflow

### Step 1: Standard Operation (Normal State)
```cpp
Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", false);
// Device is registered and entities are available in Home Assistant
```

### Step 2: Prepare for Removal
Edit your code to set `unregisterDevices` to `true`:
```cpp
Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", true);
//                                                            ^^^^
//                                                           true = unregister
```

⚠️ **Important**: Only the entities defined in this code will be removed. If you previously had different entities with different names, they will remain in Home Assistant and must be manually deleted.

### Step 3: Flash the Device
Upload the modified code to your ESP32. The device will:
1. Connect to WiFi and MQTT
2. Unregister all entities currently defined in the code
3. **HALT - the program stops** (intentional, nothing left to do)
4. No further action or monitoring occurs

**The serial monitor will show completion, then the device effectively stops communicating.**

### Step 4: Verify Removal
- Check Home Assistant - only the entities from this code should be gone
- **Important**: Manually delete any orphaned entities from older code versions
- Check MQTT - discovery topics for current entities should be gone

### Step 5: Return to Normal (REQUIRED to use device again)
**You MUST do this if you want the device to work again:**
1. Change `unregisterDevices` back to `false` in your code
2. Flash the device
3. The device will re-register and entities will work normally

**If you don't remove the `true` flag, the device will keep halting after removal.**

## Technical Details

### What Happens During Unregistration

When `unregisterDevices = true`:
1. Manager connects to WiFi and MQTT
2. Unregisters **only** entities currently defined in this code
3. Publishes removal messages to Home Assistant
4. Does NOT register new entities
5. Does NOT continue the loop - program halts
6. Device becomes idle (no further MQTT communication)

**Entities not in current code are untouched** - they remain in Home Assistant and must be manually removed

### MQTT Topics Involved

- All entity-specific discovery topics are unregistered
- Device availability state is updated
- Configuration payloads are removed

## Examples

### Example 1: Temporary Device Removal
```cpp
void setup() {
  // Set to true only during this session
  if (some_condition) {
    Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", true);
  } else {
    Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", false);
  }
}
```

### Example 2: Automatic Cleanup via Button
```cpp
bool shouldCleanup = false;

void onCleanupButton() {
  shouldCleanup = true;
  delay(100);
  ESP.restart(); // Restart with cleanup on next boot
}

void setup() {
  cleanupButton.setCommandCallback(onCleanupButton);
  
  // Check a flag or storage to determine cleanup
  // For now, just normal operation
  Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", false);
}
```

## Safety Notes

- **Program halts after removal** - the device stops all activity. This is normal.
- **Only current entities are removed** - backups of old entity names remain and must be manually deleted from Home Assistant
- **Must flip flag back to false** - if you want to use the device again, you MUST set `unregisterDevices = false` and reflash
- **Unregistration is immediate** - settings are sent on first MQTT connect, then program halts
- Automations in Home Assistant that reference removed entities may stop working
- Always have your code backed up before flashing with `unregisterDevices = true`
- After removal, manually delete any orphaned entities from Home Assistant that aren't in your current code

## Troubleshooting

**Issue:** Some entities still appear in Home Assistant
- **Cause:** Those entities aren't in your current code (renamed or removed in older versions)
- **Solution:** Manually delete them from Home Assistant's device config
- **Note:** Device removal only removes entities defined in the current code

**Issue:** Device not responding at all after removal
- **Expected behavior** - the program halts after removal. No entities = no communication
- **Solution:** Set `unregisterDevices = false` and reflash to make it active again

**Issue:** Device still sending data after removal attempt
- **Cause:** Likely MQTT connectivity failed during removal
- **Solution:** Check WiFi/MQTT connection, verify broker has MQTT discovery enabled
- **Solution:** Set `unregisterDevices = true` again and reflash

**Issue:** Cannot re-register device after removal
- **Cause:** Forgot to change `unregisterDevices` back to `false`
- **Solution:** Edit code, set flag to `false`, and reflash
- **Solution:** Ensure WiFi and MQTT credentials are correct
- **Note:** Device will not resume normal operation until flag is removed
