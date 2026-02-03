#include "Button.h"
#include "../HomeAssistantManager.h"

namespace HA {
  ButtonBase::ButtonBase(Manager *mgr, const char *name) : Device(mgr) {
    m_name = name;
    m_type = DeviceType::BUTTON;
    m_commandTopic = "homeassistant/button/" + String(name) + "_" + m_DeviceId + "/command";
  }

  void ButtonBase::m_handleCallback(String payload) {
    Log.infoln("Button command received for: %s, Payload: %s", m_name, payload);
    RunCallback();
  }

  Button::Generic::Generic(Manager *mgr, const char *name) : ButtonBase(mgr, name) {
    InitDevice();
  }

  Button::Restart::Restart(Manager *mgr, const char *name) : ButtonBase(mgr, name) {
    m_deviceClass = "restart";
    setCommandCallback(RestartCallback);
    InitDevice();
  };

  void Button::Restart::RestartCallback() {
    Log.fatalln("Restart command received. Restarting device...");
    ESP.restart();
  }
}