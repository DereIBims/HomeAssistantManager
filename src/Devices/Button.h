#pragma once
#include "../Device.h"

namespace HA {
  class Manager;
  class ButtonBase : public Device, public CallbackMixin<> {
    friend class Manager;

public:
    ButtonBase(Manager *mgr, const char *name, bool DIAGNOSTIC = false);

private:
    void m_handleCallback(String payload) override;
public:
    void setState(const char *STATE) = delete;
    void setState(String &STATE) = delete;
  };

  class Button {
public:
    class Generic : public ButtonBase {
  public:
      Generic(Manager *mgr, const char *name, bool DIAGNOSTIC = false);
    };

    class Restart : public ButtonBase {
  public:
      Restart(Manager *mgr, const char *name, bool DIAGNOSTIC = false);
  protected:
      static void RestartCallback();
    };
  };
}
