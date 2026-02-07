#pragma once
#include "../Device.h"

namespace HA {
  class Manager;
  class SwitchBase : public Device, public CallbackMixin<bool> {
    friend class Manager;

public:
    SwitchBase(Manager *mgr, const char *name);
    void setValue(bool STATE);

private:
    void m_handleCallback(String payload) override;
  };

  class Switch {
public:
    class Generic : public SwitchBase {
        public:
        Generic(Manager *mgr, const char *name);
    };

    class Outlet : public SwitchBase {
        public:
        Outlet(Manager *mgr, const char *name);
    };
  };
}