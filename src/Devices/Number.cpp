#include "Number.h"
#include "../HomeAssistantManager.h"
#include <cmath>
#include <cstdlib>

namespace HA {
  NumberBase::NumberBase(Manager *mgr, const char *name, float min, float max, float step, const char *unit)
      : Device(mgr), m_min(min), m_max(max), m_step(step)
  {
    m_name = name;
    m_deviceType = "number";
    m_unit = unit;
    if (std::isfinite(min) && std::isfinite(max) && min < max && std::isfinite(step) && step >= 0.001f) {
      m_commandTopic = getTopicBase() + "/command";
      m_stateTopic = getTopicBase() + "/state";
    }
  }

  void NumberBase::configureEntity(JsonObject config)
  {
    config["min"] = m_min;
    config["max"] = m_max;
    config["step"] = m_step;
  }

  bool NumberBase::isValidValue(float value) const
  {
    return std::isfinite(value) && value >= m_min && value <= m_max;
  }

  bool NumberBase::setValue(float VALUE)
  {
    if (!isValidValue(VALUE)) {
      return false;
    }
    char state[24];
    snprintf(state, sizeof(state), "%.9g", static_cast<double>(VALUE));
    return publishState(state, true);
  }

  void NumberBase::m_handleCallback(String payload)
  {
    const char *start = payload.c_str();
    char *end;
    float value = strtof(start, &end);
    if (end == start || end != start + payload.length() || !isValidValue(value)) {
      Log.errorln("Invalid number command for: %s", m_name);
      return;
    }
    RunCallback(value);
  }

  Number::Generic::Generic(Manager *mgr, const char *name, float min, float max, float step, const char *unit)
      : NumberBase(mgr, name, min, max, step, unit)
  {
    if (m_stateTopic.length()) {
      InitDevice();
    }
  }
}
