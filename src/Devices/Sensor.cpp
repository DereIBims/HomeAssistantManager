#include "Sensor.h"
#include "../GenericSensors.h"
#include "../HomeAssistantManager.h"

namespace HA {
  SensorBase::SensorBase(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *stateClass) : Device(mgr) {
    m_name = name;
    m_deviceClass = sensorClass;
    m_unit = unit;
    m_stateClass = stateClass;
    m_stateTopic = "homeassistant/sensor/" + String(name) + "_" + m_DeviceId + "/state";
    m_type = DeviceType::SENSOR;
  }

  void SensorBase::m_handleCallback(String payload) {} // No callback for sensors

  void SensorBase::setValue(float STATE, int decimalPlaces) {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      String state = String(STATE, decimalPlaces);
      manager->mqttClient.publish(m_stateTopic.c_str(), state.c_str(), false);
    }
  }

  void SensorBase::setValue(int STATE) {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      String state = String(STATE);
      manager->mqttClient.publish(m_stateTopic.c_str(), state.c_str(), false);
    }
  }

  void SensorBase::setValue(long STATE) {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      String state = String(STATE);
      manager->mqttClient.publish(m_stateTopic.c_str(), state.c_str(), false);
    }
  }

  void SensorBase::setValue(double STATE, int decimalPlaces) {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      String state = String(STATE, decimalPlaces);
      manager->mqttClient.publish(m_stateTopic.c_str(), state.c_str(), false);
    }
  }

  Sensor::Generic::Generic(Manager *mgr, const char *name, SensorClass sensorClass, const char *stateClass) : SensorBase(mgr, name, sensorClass.deviceClass, sensorClass.defaultUnit, stateClass) {
    InitDevice();
  }
  Sensor::Generic::Generic(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *stateClass) : SensorBase(mgr, name, sensorClass, unit, stateClass) {
    InitDevice();
  }
  Sensor::Diag::Diag(Manager *mgr, const char *name, SensorClass sensorClass, const char *stateClass) : SensorBase(mgr, name, sensorClass.deviceClass, sensorClass.defaultUnit, stateClass) {
    m_entityCategory = "diagnostic";
    InitDevice();
  }
  Sensor::Diag::Diag(Manager *mgr, const char *name, const char *sensorClass, const char *unit, const char *stateClass) : SensorBase(mgr, name, sensorClass, unit, stateClass) {
    m_entityCategory = "diagnostic";
    InitDevice();
  }
  Sensor::Diag::AutoFreeHeap::AutoFreeHeap(Manager *mgr, const char *name) : SensorBase(mgr, name, nullptr, "B", HA::MEASUREMENT) {
    m_entityCategory = "diagnostic";
    m_diagType = AutoDiagType::HEAP;
    InitDevice();
  }
  Sensor::Diag::AutoRSSI::AutoRSSI(Manager *mgr, const char *name) : SensorBase(mgr, name, HA::SignalStrength.deviceClass, HA::SignalStrength.defaultUnit, HA::MEASUREMENT) {
    m_entityCategory = "diagnostic";
    m_diagType = AutoDiagType::RSSI;
    InitDevice();
  }
  Sensor::Diag::AutoUptime::AutoUptime(Manager *mgr, const char *name) : SensorBase(mgr, name, "duration", "s", HA::MEASUREMENT) {
    m_entityCategory = "diagnostic";
    m_diagType = AutoDiagType::UPTIME;
    InitDevice();
  }
  Sensor::Diag::AutoResetReason::AutoResetReason(Manager *mgr, const char *name) : SensorBase(mgr, name, nullptr, nullptr, nullptr) {
    m_entityCategory = "diagnostic";
    m_diagType = AutoDiagType::RESET;
    InitDevice();
  }
}
