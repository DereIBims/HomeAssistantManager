#include <HomeAssistantManager.h>

// Manager constructor: (Wi-Fi SSID, Wi-Fi password, MQTT broker hostname or IP, log level = LOG_LEVEL_INFO)
HA::Manager Manager("your-ssid", "your-password", "mqtt-host");

// Create some example entities
// Button::Generic constructor: (manager, entity display name, diagnostic category = false)
HA::Button::Generic cleanupButton(&Manager, "Cleanup Device");

void onCleanupButton() {
  Serial.println("Cleanup triggered - call begin() with unregisterDevices=true next startup");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // setCommandCallback(function called on button press, with no arguments)
  cleanupButton.setCommandCallback(onCleanupButton);
  
  // ============================================================================
  // DEVICE REMOVAL - CRITICAL BEHAVIOR
  // ============================================================================
  // 
  // The unregisterDevices parameter controls whether entities are removed:
  //
  // unregisterDevices = false (default):
  //   - Normal operation
  //   - Device registers and stays registered
  //   - Entities work normally
  //   - Program continues running
  //
  // unregisterDevices = true:
  //   ⚠️ REMOVES ONLY entities defined in THIS code
  //   ⚠️ OLD/RENAMED entities will NOT be removed (delete manually in HA)
  //   ⚠️ PROGRAM HALTS AFTER REMOVAL (nothing left to do)
  //   ⚠️ MUST change back to false to use device again
  //
  // Example removal code:
  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  // bool success = Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", true);
  //                                                                              ^^^^
  //                                                                        Set to true
  //
  // WORKFLOW TO REMOVE DEVICE:
  // 1. Change unregisterDevices to true below
  // 2. Flash the device
  // 3. Device connects, unregisters current entities, then HALTS
  // 4. Check Home Assistant - only entities from this code are gone
  // 5. IMPORTANT: Manually delete any old/orphaned entities
  // 6. Change unregisterDevices back to false
  // 7. Flash again to use device normally
  //
  // ============================================================================
  
  // Manager.begin(device name, manufacturer, model, firmware version, unregister entities = false)
  bool success = Manager.begin("ESP32_Device", "MyCompany", "ESP32", "1.0.0", false);
  //                                                                         ^^^^
  //                                                           Change to true to remove
  
  // NOTE: If unregisterDevices = true, the program halts here!
  // The following code will NOT execute in removal mode.
  // Only reachable when unregisterDevices = false
  
  if (!success) {
    Serial.println("Failed to initialize Manager");
    while (true) {
      delay(1000);
    }
  }
  
  Serial.println("Setup complete - Device is operational");
}

void loop() {
  Manager.loop();
}
