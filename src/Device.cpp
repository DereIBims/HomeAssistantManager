#include "Device.h"
#include "HomeAssistantManager.h"

namespace HA {

  Device::Device(Manager *mgr) : manager(mgr) {
  }

  Device::~Device() {
    if (manager) {
      manager->removeDevice(this);
    }
  }

  const String &Device::getDeviceId() {
    static const String DeviceId = String(ESP.getEfuseMac(), HEX);
    return DeviceId;
  }

  void Device::InitDevice() {
    m_stateTopic.replace(" ", "_");
    m_commandTopic.replace(" ", "_");
    manager->addDevice(this);
  }

  static bool isTopicIdChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_' || c == '-';
  }

  String Device::getTopicBase() const {
    String id = m_entityId.length() ? m_entityId : String(m_name);
    for (size_t i = 0; i < id.length(); i++) {
      if (!isTopicIdChar(id[i])) {
        id[i] = '_';
      }
    }
    return "homeassistant/" + m_deviceType + "/" + id + "_" + getDeviceId();
  }

  bool Device::setEntityId(const char *id) {
    if (!manager || manager->m_started || !id || !*id) {
      return false;
    }
    for (const char *c = id; *c; c++) {
      if (!isTopicIdChar(*c)) {
        return false;
      }
    }
    String oldTopic = getTopicBase();
    if (!m_entityId.reserve(strlen(id))) {
      return false;
    }
    m_entityId = id;
    String topic = getTopicBase();
    if (m_stateTopic == oldTopic + "/state") {
      m_stateTopic = topic + "/state";
    }
    if (m_commandTopic == oldTopic + "/command") {
      m_commandTopic = topic + "/command";
    }
    return true;
  }

  bool Device::publishState(const char *state, bool retained) {
    if (!manager || !m_stateTopic.length()) {
      return false;
    }
    if (manager->mqttClient.publish(m_stateTopic.c_str(), state, retained)) {
      Log.infoln("Updated state for: %s", m_name);
      return true;
    }
    return false;
  }

  void Device::setState(const char *STATE) {
    publishState(STATE);
  }

  void Device::setState(String &STATE) {
    setState(STATE.c_str());
  }

  void Device::registerEntity() {
    manager->DeviceInfo.clear();
    manager->DeviceInfo["dev"] = manager->ManagerInfo;
    manager->DeviceInfo["name"] = m_name;
    String id = m_entityId.length() ? m_entityId : String(m_name);
    manager->DeviceInfo["uniq_id"] = id + "_" + getDeviceId();
    manager->DeviceInfo["avty_t"] = manager->availTopic;
    manager->DeviceInfo["pl_avail"] = "online";
    manager->DeviceInfo["pl_not_avail"] = "offline";
    if (m_stateTopic.length() > 0) {
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
      manager->DeviceInfo["cmd_t"] = m_commandTopic;
    }
    if (m_valueTemplate && *m_valueTemplate) {
      manager->DeviceInfo["val_tpl"] = m_valueTemplate;
    }

    configureEntity(manager->DeviceInfo.as<JsonObject>());
    if (manager->DeviceInfo.overflowed()) {
      Log.errorln("Failed to build discovery config for: %s", m_name);
      return;
    }

    String topic = getTopicBase() + "/config";
    size_t configSize = measureJson(manager->DeviceInfo);
    if (configSize + topic.length() + MQTT_MAX_HEADER_SIZE + 2 > manager->mqttClient.getBufferSize()) {
      Log.errorln("Discovery config too large for: %s", m_name);
      return;
    }

    String config;
    if (!config.reserve(configSize) || serializeJson(manager->DeviceInfo, config) != configSize || config.length() != configSize) {
      Log.errorln("Failed to serialize discovery config for: %s", m_name);
      return;
    }

    if (manager->mqttClient.publish(topic.c_str(), reinterpret_cast<const uint8_t *>(config.c_str()), configSize, true)) {
      Log.infoln("Registered device: %s on topic: %s", m_name, topic.c_str());
    } else {
      Log.errorln("Failed to register, ERROR: %d", manager->mqttClient.state());
    }

  }

  void Device::unregisterEntity() {
    String topic = getTopicBase() + "/config";
    if (manager->mqttClient.publish(topic.c_str(), nullptr, 0, true)) {
      Log.infoln("Unregistered device: %s on topic: %s", m_name, topic.c_str());
    } else {
      Log.errorln("Failed to unregister, ERROR: %d", manager->mqttClient.state());
    }
  }

  void Device::subscribeEntity() {
    if (m_commandTopic.length() > 0) {
      if (manager->mqttClient.subscribe(m_commandTopic.c_str())) {
        Log.infoln("Subscribed to topic: %s for device: %s", m_commandTopic.c_str(), m_name);
      } else {
        Log.errorln("Failed to subscribe to topic: %s", m_commandTopic.c_str());
      }
    }
  }

} // namespace HA