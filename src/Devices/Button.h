#pragma once
#include "../Device.h"
#include <ArduinoJson.h>

namespace HA {
  class Manager;
  class ButtonBase : public Device, public CallbackMixin<> {
    friend class Manager;

public:
    ButtonBase(Manager *mgr, const char *name);

private:
    void m_handleCallback(String payload) override;
  };

  class Button {
public:
    class Generic : public ButtonBase {
  public:
      Generic(Manager *mgr, const char *name);
    };

    class Restart : public ButtonBase {
  public:
      Restart(Manager *mgr, const char *name);
      static void RestartCallback();
    };
  };
}
