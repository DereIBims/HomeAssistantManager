#include "Event.h"
#include <algorithm>

namespace HA {
  EventBase::EventBase(Manager *mgr, const char *name, std::initializer_list<const char *> eventTypes, const char *deviceClass) : Device(mgr)
  {
    m_name = name;
    m_deviceType = "event";
    m_deviceClass = deviceClass;
    for (const char *eventType : eventTypes) {
      if (eventType && *eventType && std::find(m_eventTypes.begin(), m_eventTypes.end(), eventType) == m_eventTypes.end()) {
        m_eventTypes.emplace_back(eventType);
      }
    }
    if (!m_eventTypes.empty()) {
      m_stateTopic = getTopicBase() + "/state";
    }
  }

  void EventBase::configureEntity(JsonObject config)
  {
    JsonArray eventTypes = config["event_types"].to<JsonArray>();
    for (const auto &eventType : m_eventTypes) {
      eventTypes.add(eventType);
    }
  }

  void EventBase::m_handleCallback(String payload) {} // No callback for events

  bool EventBase::trigger(const String &EVENT_TYPE)
  {
    if (std::find(m_eventTypes.begin(), m_eventTypes.end(), EVENT_TYPE) == m_eventTypes.end()) {
      return false;
    }
    JsonDocument event;
    event["event_type"] = EVENT_TYPE;
    String payload;
    size_t size = measureJson(event);
    return !event.overflowed() && serializeJson(event, payload) == size && payload.length() == size &&
           publishState(payload.c_str());
  }

  Event::Generic::Generic(Manager *mgr, const char *name, std::initializer_list<const char *> eventTypes, const char *deviceClass)
      : EventBase(mgr, name, eventTypes, deviceClass)
  {
    if (m_stateTopic.length()) {
      InitDevice();
    }
  }
}
