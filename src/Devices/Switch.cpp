#include "Switch.h"
#include "../HomeAssistantManager.h"

namespace HA {
  SwitchBase::SwitchBase(Manager *mgr, const char *name) : Device(mgr)
  {
    m_name = name;
    m_deviceType = "switch";
    m_commandTopic = "homeassistant/switch/" + String(name) + "_" + m_DeviceId + "/command";
    m_stateTopic = "homeassistant/switch/" + String(name) + "_" + m_DeviceId + "/state";
  }

  void SwitchBase::m_handleCallback(String payload)
  {
    Log.infoln("Switch command received for: %s, Payload: %s", m_name, payload);
    if (payload.equalsIgnoreCase("ON")) {
      setValue(true);
      RunCallback(true);
    }
    else if (payload.equalsIgnoreCase("OFF")) {
      setValue(false);
      RunCallback(false);
    }
    else {
      Log.errorln("Invalid payload for switch: %s. Expected 'ON' or 'OFF'. Received: %s", m_name, payload);
    }
  }

  void SwitchBase::setValue(bool STATE)
  {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      String state = STATE ? "ON" : "OFF";
      manager->mqttClient.publish(m_stateTopic.c_str(), state.c_str(), false);
    }
  }

  Switch::Generic::Generic(Manager *mgr, const char *name) : SwitchBase(mgr, name)
  {
    m_deviceClass = "switch";
    InitDevice();
  }

  Switch::Outlet::Outlet(Manager *mgr, const char *name) : SwitchBase(mgr, name)
  {
    m_deviceClass = "outlet";
    InitDevice();
  }
}