#pragma once
#include "../GenericSensors.h"
#include "../Device.h"
#include <ArduinoJson.h>

namespace HA {
  class Manager;
  class SensorBase : public Device {
    friend class Manager;

public:
    SensorBase(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *StateClass = "measurement");

    void setValue(float VALUE, int decimalPlaces = 1);
    void setValue(int VALUE);
    void setValue(long VALUE);
    void setValue(double VALUE, int decimalPlaces = 1);

private:
    void m_handleCallback(String payload) override;
  };

  class Sensor {
public:
    class Generic : public SensorBase {
  public:
      Generic(Manager *mgr, const char *name, SensorClass sensorClass, const char *StateClass = "measurement");
      Generic(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *StateClass = "measurement");
    };

    class Diag : public SensorBase {
  public:
      Diag(Manager *mgr, const char *name, SensorClass sensorClass, const char *StateClass = "measurement");
      Diag(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *StateClass = "measurement");

      class AutoRSSI : public SensorBase {
    public:
        AutoRSSI(Manager *mgr, const char *name);
      };
      class AutoUptime : public SensorBase {
    public:
        AutoUptime(Manager *mgr, const char *name);
      };
      class AutoFreeHeap : public SensorBase {
    public:
        AutoFreeHeap(Manager *mgr, const char *name);
      };
      class AutoResetReason : public SensorBase {
    public:
        AutoResetReason(Manager *mgr, const char *name);
      };
    };
  };
}
