#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <functional>
#include <utility>

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
    static const String &getDeviceId();
    String getTopicBase() const;
    const char *m_name = nullptr;
    const char *m_sensorClass = nullptr;
    const char *m_unit = nullptr;
    const char *m_stateClass = nullptr;
    const char *m_deviceClass = nullptr;
    const char *m_entityCategory = nullptr;
    const char *m_valueTemplate = nullptr;
    void InitDevice();
    virtual void configureEntity(JsonObject config) {}
    bool publishState(const char *state, bool retained = false);
    virtual void m_handleCallback(String payload) = 0;

private:
    String m_entityId;
    void registerEntity();
    void subscribeEntity();
    void unregisterEntity();

public:
    Device(Manager *mgr);
    virtual ~Device();
    bool setEntityId(const char *id);
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