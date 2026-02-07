#include "BinarySensor.h"
#include "../HomeAssistantManager.h"

namespace HA {
  BinarySensorBase::BinarySensorBase(Manager *mgr, const char *name, const char *sensorClass) : Device(mgr)
  {
    m_name = name;
    m_deviceClass = sensorClass;
    m_stateTopic = "homeassistant/binary_sensor/" + String(name) + "_" + m_DeviceId + "/state";
    m_deviceType = "binary_sensor";
  }

  void BinarySensorBase::m_handleCallback(String payload) {} // No callback for binary sensors

  void BinarySensorBase::setValue(bool STATE)
  {
    Log.infoln("Updated state for: %s", m_name);
    String state = STATE ? "ON" : "OFF";
    manager->mqttClient.publish(m_stateTopic.c_str(), state.c_str(), false);
  }

  BinarySensor::Generic::Generic(Manager *mgr, const char *name, const char *sensorClass)
      : BinarySensorBase(mgr, name, sensorClass)
  {
    InitDevice();
  }
}