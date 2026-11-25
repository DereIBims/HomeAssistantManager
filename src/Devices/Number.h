#pragma once
#include "../Device.h"

namespace HA {
  class NumberBase : public Device, public CallbackMixin<float> {
public:
    NumberBase(Manager *mgr, const char *name, float min, float max, float step = 1, const char *unit = nullptr);
    bool setValue(float VALUE);

private:
    void configureEntity(JsonObject config) override;
    void m_handleCallback(String payload) override;
    bool isValidValue(float value) const;
    float m_min;
    float m_max;
    float m_step;
  };

  class Number {
public:
    class Generic : public NumberBase {
  public:
      Generic(Manager *mgr, const char *name, float min, float max, float step = 1, const char *unit = nullptr);
    };
  };
}
