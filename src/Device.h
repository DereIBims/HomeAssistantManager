#pragma once
#include "ArduinoJson.h"

namespace HA {
  class Manager;
  enum struct DeviceType : uint8_t {
    SENSOR,
    BUTTON,
    BINARY_SENSOR
  };
  enum struct AutoDiagType : uint8_t {
    NONE,
    HEAP,
    RSSI,
    RESET,
    UPTIME
  };

  constexpr const char *getDeviceType(DeviceType type) {
    switch (type) {
    case DeviceType::SENSOR:
      return "sensor";
    case DeviceType::BUTTON:
      return "button";
    case DeviceType::BINARY_SENSOR:
      return "binary_sensor";
    default:
      return "Unknown";
    }
  };

  class Device {
    friend class Manager;

protected:
    Manager *manager;
    DeviceType m_type;
    AutoDiagType m_diagType = AutoDiagType::NONE;
    String m_commandTopic = "";
    String m_stateTopic = "";
    inline static String m_DeviceId = String(ESP.getEfuseMac(), HEX);
    const char *m_name = nullptr;
    const char *m_sensorClass = nullptr;
    const char *m_unit = nullptr;
    const char *m_stateClass = nullptr;
    const char *m_deviceClass = nullptr;
    const char *m_entityCategory = nullptr;
    const char *m_valueTemplate = nullptr;
    void InitDevice();
    virtual void m_handleCallback(String payload) = 0;

private:
    void registerEntity();
    void subscribeEntity();

public:
    Device(Manager *mgr);
    void setState(const char *STATE);
    void setState(String &STATE);
  };

  template <typename... Args>
  class CallbackMixin {
    friend class Manager;

public:
    using Callback = std::function<void(Args...)>;
    void setCommandCallback(Callback cb) { m_callback = std::move(cb); }

protected:
    void RunCallback(Args... args) {
      if (m_callback)
        m_callback(std::forward<Args>(args)...);
    }

private:
    Callback m_callback;
  };

} // namespace HASS