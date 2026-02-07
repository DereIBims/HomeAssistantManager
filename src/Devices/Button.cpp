#include "Button.h"
#include "../HomeAssistantManager.h"

namespace HA {
  ButtonBase::ButtonBase(Manager *mgr, const char *name, bool DIAGNOSTIC) : Device(mgr) {
    m_name = name;
    m_deviceType = "button";
    m_commandTopic = "homeassistant/button/" + String(name) + "_" + m_DeviceId + "/command";
    if(DIAGNOSTIC) m_entityCategory = "diagnostic";
  }

  void ButtonBase::m_handleCallback(String payload) {
    Log.infoln("Button command received for: %s, Payload: %s", m_name, payload);
    RunCallback();
  }

  Button::Generic::Generic(Manager *mgr, const char *name, bool DIAGNOSTIC) : ButtonBase(mgr, name, DIAGNOSTIC) {
    InitDevice();
  }

  Button::Restart::Restart(Manager *mgr, const char *name, bool DIAGNOSTIC) : ButtonBase(mgr, name, DIAGNOSTIC) {
    m_deviceClass = "restart";
    setCommandCallback(RestartCallback);
    InitDevice();
  };

  void Button::Restart::RestartCallback() {
    Log.fatalln("Restart command received. Restarting device...");
    ESP.restart();
  }
}