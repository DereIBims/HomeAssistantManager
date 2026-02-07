#pragma once
#include "ArduinoJson.h"

namespace HA {
  class Manager;
  enum struct AutoDiagType : uint8_t {
    NONE,
    HEAP,
    RSSI,
    RESET,
    UPTIME
  };

  class Device {
    friend class Manager;
    friend class StateMixin;

protected:
    Manager *manager;
    AutoDiagType m_diagType = AutoDiagType::NONE;
    String m_deviceType;
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
    void unregisterEntity();

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
    void RunCallback(Args... args)
    {
      if (m_callback)
        m_callback(std::forward<Args>(args)...);
    }

private:
    Callback m_callback;
  };

} // namespace HASS