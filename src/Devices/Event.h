#pragma once
#include "../Device.h"
#include <initializer_list>
#include <vector>

namespace HA {
  class EventBase : public Device {
public:
    EventBase(Manager *mgr, const char *name, std::initializer_list<const char *> eventTypes, const char *deviceClass = nullptr);
    bool trigger(const String &EVENT_TYPE);

private:
    void configureEntity(JsonObject config) override;
    void m_handleCallback(String payload) override;
    std::vector<String> m_eventTypes;
  };

  class Event {
public:
    class Generic : public EventBase {
  public:
      Generic(Manager *mgr, const char *name, std::initializer_list<const char *> eventTypes, const char *deviceClass = nullptr);
    };
  };
}
