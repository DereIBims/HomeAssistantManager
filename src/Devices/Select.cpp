#include "Select.h"
#include "../HomeAssistantManager.h"
#include <algorithm>

namespace HA {
  SelectBase::SelectBase(Manager *mgr, const char *name, std::initializer_list<const char *> options) : Device(mgr)
  {
    m_name = name;
    m_deviceType = "select";
    m_commandTopic = getTopicBase() + "/command";
    m_stateTopic = getTopicBase() + "/state";
    for (const char *option : options) {
      if (option && *option && strcmp(option, "None") != 0 && !isValidOption(option)) {
        m_options.emplace_back(option);
      }
    }
  }

  void SelectBase::configureEntity(JsonObject config)
  {
    JsonArray options = config["options"].to<JsonArray>();
    for (const auto &option : m_options) {
      options.add(option);
    }
  }

  bool SelectBase::isValidOption(const String &value) const
  {
    return std::find(m_options.begin(), m_options.end(), value) != m_options.end();
  }

  bool SelectBase::setValue(const String &VALUE)
  {
    return isValidOption(VALUE) && publishState(VALUE.c_str(), true);
  }

  void SelectBase::m_handleCallback(String payload)
  {
    if (!isValidOption(payload)) {
      Log.errorln("Invalid select command for: %s", m_name);
      return;
    }
    RunCallback(payload);
  }

  Select::Generic::Generic(Manager *mgr, const char *name, std::initializer_list<const char *> options)
      : SelectBase(mgr, name, options)
  {
    InitDevice();
  }
}
