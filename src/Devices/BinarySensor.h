#pragma once
#include "../GenericSensors.h"
#include "../Device.h"
#include <ArduinoJson.h>

namespace HA {
  class Manager;

  class BinarySensorBase : public Device {
    friend class Manager;

public:
    BinarySensorBase(Manager *mgr, const char *name, const char *sensorClass);
    void setValue(bool STATE);

private:
    void m_handleCallback(String payload) override;
  };

  class BinarySensor {
public:
    class Generic : public BinarySensorBase {
  public:
      Generic(Manager *mgr, const char *name, const char *sensorClass);
    };
  };
}