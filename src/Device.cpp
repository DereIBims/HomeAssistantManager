#include "Device.h"
#include "HomeAssistantManager.h"

namespace HA {

  Device::Device(Manager *mgr) : manager(mgr) {
  }

  void Device::InitDevice() {
    manager->addDevice(this);
  }

  void Device::setState(const char *STATE) {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      manager->mqttClient.publish(m_stateTopic.c_str(), STATE, false);
    }
  }

  void Device::setState(String &STATE) {
    if (m_stateTopic.length() > 0) {
      Log.infoln("Updated state for: %s", m_name);
      manager->mqttClient.publish(m_stateTopic.c_str(), STATE.c_str(), false);
    }
  }

  void Device::registerEntity() {
    manager->DeviceInfo.clear();
    manager->DeviceInfo["dev"] = manager->ManagerInfo;
    manager->DeviceInfo["name"] = m_name;
    manager->DeviceInfo["uniq_id"] = String(m_name) + "_" + m_DeviceId;
    manager->DeviceInfo["avty_t"] = manager->availTopic;
    manager->DeviceInfo["pl_avail"] = "online";
    manager->DeviceInfo["pl_not_avail"] = "offline";
    if (m_stateTopic.length() > 0) {
      m_stateTopic.replace(" ", "_");
      manager->DeviceInfo["stat_t"] = m_stateTopic;
    }
    if (m_deviceClass && *m_deviceClass) {
      manager->DeviceInfo["dev_cla"] = m_deviceClass;
    }
    if (m_stateClass && *m_stateClass) {
      manager->DeviceInfo["stat_cla"] = m_stateClass;
    }
    if (m_unit && *m_unit) {
      manager->DeviceInfo["unit_of_meas"] = m_unit;
    }
    if (m_entityCategory && *m_entityCategory) {
      manager->DeviceInfo["ent_cat"] = m_entityCategory;
    }
    if (m_commandTopic.length() > 0) {
      m_commandTopic.replace(" ", "_");
      manager->DeviceInfo["cmd_t"] = m_commandTopic;
    }
    if (m_valueTemplate && *m_valueTemplate) {
      manager->DeviceInfo["val_tpl"] = m_valueTemplate;
    }

    String topic = "homeassistant/" + String(getDeviceType(m_type)) + "/" + manager->DeviceInfo["name"].as<String>() + "_" + m_DeviceId + "/config";
    topic.replace(" ", "_");
    char config[512];
    serializeJson(manager->DeviceInfo, config);

    if (manager->mqttClient.publish(topic.c_str(), config, true)) {
      Log.infoln("Registered device: %s on topic: %s", m_name, topic.c_str());
    } else {
      Log.errorln("Failed to register, ERROR: %d", manager->mqttClient.state());
    }
  }

  void Device::subscribeEntity() {
    if (m_commandTopic.length() > 0) {
      manager->mqttClient.subscribe(m_commandTopic.c_str());
      Log.infoln("Subscribed to topic: %s for device: %s", m_commandTopic.c_str(), m_name);
    }
  }

} // namespace HASSDevice