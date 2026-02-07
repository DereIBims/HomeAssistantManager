#pragma once

#if !defined(ARDUINO_ARCH_ESP32)
#error "ESP32 only"
#endif

#include "Constants.h"
#include <Arduino.h>
#include <ArduinoJSON.h>
#include <ArduinoLog.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <vector>

#define SERIAL_BAUD 115200

namespace HA {
  class Device;
  class Manager {
    friend class Device;
    friend class BinarySensorBase;
    friend class SensorBase;
    friend class SwitchBase;

public:
    Manager(const char *WiFi_SSID, const char *WiFi_PASS, const char *MQTT_SERVER, int LOG_LEVEL = LOG_LEVEL_INFO);

    void setMqttPort(uint16_t MQTT_PORT);
    void setMqttCredentials(const char *MQTT_USER, const char *MQTT_PASS);
    void setAutoDiagInterval(unsigned long interval);

    bool begin(const char *DEVICE_NAME, const char *DEVICE_MANUFACTURER, const char *DEVICE_MODEL, const char *DEVICE_SW_VERSION, bool UnregisterDevices = false);

    void loop();

private:
    WiFiClient m_wifiClient;

    const char *m_wifiSsid = nullptr;
    const char *m_wifiPass = nullptr;
    const char *m_mqttServer = nullptr;
    const char *m_mqttUser = nullptr;
    const char *m_mqttPass = nullptr;
    int m_loglevel;
    unsigned long m_AutoDiagInterval = 30000;
    uint16_t m_mqttPort = 1883;
    String availTopic;

    JsonDocument ManagerInfo;
    JsonDocument DeviceInfo;
    PubSubClient mqttClient;

    const String GetRestartString(esp_reset_reason_t reason);

    std::vector<Device *> m_devices;
    void m_registerDevices();
    void m_subsribeTopics();
    void addDevice(Device *device);
    bool m_connect();
    void m_updateAutoDiag(bool SkipTimer = false);
    void m_mqttCallback(char *topic, byte *payload, unsigned int length);
    void m_unregisterDevices();
  };
}
