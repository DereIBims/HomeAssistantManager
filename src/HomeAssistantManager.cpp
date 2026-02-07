#include "HomeAssistantManager.h"
#include "Device.h"

namespace HA {

  unsigned long LastAutoDiagUpdate = 0;

  Manager::Manager(const char *WiFi_SSID, const char *WiFi_PASS, const char *MQTT_SERVER, int LOG_LEVEL)
      : m_wifiSsid(WiFi_SSID), m_wifiPass(WiFi_PASS), m_mqttServer(MQTT_SERVER), mqttClient(m_wifiClient), m_loglevel(LOG_LEVEL)
  {
    mqttClient.setBufferSize(1024);
    mqttClient.setCallback([this](char *t, byte *p, unsigned int l) { m_mqttCallback(t, p, l); });
    String DeviceId = String(ESP.getEfuseMac(), HEX);
    ManagerInfo["identifiers"][0] = DeviceId;
    availTopic = DeviceId + "/available";
  }

  void Manager::setMqttPort(uint16_t port)
  {
    m_mqttPort = port;
    mqttClient.setServer(m_mqttServer, m_mqttPort);
  }

  void Manager::setMqttCredentials(const char *user, const char *pass)
  {
    m_mqttUser = user;
    m_mqttPass = pass;
  }

  void Manager::setAutoDiagInterval(unsigned long interval)
  {
    m_AutoDiagInterval = interval;
  }

  bool Manager::begin(const char *name, const char *manufacturer, const char *model, const char *software_version, bool unregisterDevices)
  {

    Log.begin(m_loglevel, &Serial);

    // Validate required settings
    if (!m_wifiSsid || !*m_wifiSsid) {
      Log.errorln("WiFi SSID not set. Use a valid SSID in the constructor.");
      return false;
    }
    if (!m_wifiPass || !*m_wifiPass) {
      Log.errorln("WiFi password not set. Use a valid password in the constructor.");
      return false;
    }
    if (!m_mqttServer || !*m_mqttServer) {
      Log.errorln("MQTT server not set. Use a valid MQTT server in the constructor.");
      return false;
    }
    if (!name || !*name) {
      Log.errorln("Device name not set. Call setDeviceInfo().");
      return false;
    }
    if (!manufacturer || !*manufacturer) {
      Log.errorln("Manufacturer not set. Call setDeviceInfo().");
      return false;
    }
    if (!model || !*model) {
      Log.errorln("Model not set. Call setDeviceInfo().");
      return false;
    }
    if (!software_version || !*software_version) {
      Log.errorln("Software version not set. Call setDeviceInfo().");
      return false;
    }
    if (m_mqttPort == 1883) {
      Log.infoln("Using default MQTT port. Call setMqttPort() to change it.");
    }

    ManagerInfo["name"] = name;
    ManagerInfo["manufacturer"] = manufacturer;
    ManagerInfo["model"] = model;
    ManagerInfo["sw_version"] = software_version;

    mqttClient.setServer(m_mqttServer, m_mqttPort);

    if (m_connect()) {
      if (!unregisterDevices) {
        m_subsribeTopics();
        m_registerDevices();
        m_updateAutoDiag(true);
      }
      else {
        m_unregisterDevices();
      }
      return true;
    }
    else {
      return false;
    }
  }

  bool Manager::m_connect()
  {
    unsigned long startTime = millis();
    Log.info("Connecting to WiFi %s...", m_wifiSsid);
    WiFi.begin(m_wifiSsid, m_wifiPass);
    while (WiFi.status() != WL_CONNECTED) {
      if (millis() - startTime > 30000) { // 30 second timeout
        Log.errorln("");
        Log.errorln("WiFi connection timeout.");
        return false;
      }
      delay(500);
    }
    Log.infoln("");
    Log.infoln("WiFi connected, IP: %s", WiFi.localIP().toString().c_str());

    Log.infoln("Connecting to MQTT: %s:%d", m_mqttServer, m_mqttPort);
    startTime = millis();
    while (!mqttClient.connected()) {
      if (millis() - startTime > 30000) { // 30 second timeout
        Log.errorln("MQTT connection timeout.");
        return false;
      }
      if (mqttClient.connect(String(ESP.getEfuseMac(), HEX).c_str(), m_mqttUser, m_mqttPass, availTopic.c_str(), 1, true, "offline")) {
        Log.infoln("MQTT connected successfully");
        // subscribe to all command topics
      }
      else {
        delay(5000);
      }
    }

    mqttClient.publish(availTopic.c_str(), "online", true);

    return true;
  }

  void Manager::loop()
  {
    if (!mqttClient.connected()) {
      m_connect(); // Attempt to reconnect
    }
    mqttClient.loop();
    m_updateAutoDiag();
  }

  void Manager::m_unregisterDevices()
  {
    for (auto d : m_devices) {
      d->unregisterEntity();
    }
    Serial.println("Cleared retained MQTT configs for all devices.");
    Serial.println("Remove function call and restart the device to re-register entities with Home Assistant.");
    Serial.println("Restart the device to re-register entities with Home Assistant.");
    Serial.println("Device will now halt since entities are unregistered. Restart to re-register.");
    while (true) {
      yield();
    }
  }

  void Manager::addDevice(Device *device)
  {
    m_devices.push_back(device);
  }

  void Manager::m_registerDevices()
  {
    for (auto d : m_devices) {
      d->registerEntity();
    }
  }

  void Manager::m_subsribeTopics()
  {
    for (auto d : m_devices) {
      d->subscribeEntity();
    }
  }

  void Manager::m_mqttCallback(char *topic, byte *payload, unsigned int length)
  {
    String t = topic;
    String p;
    for (unsigned int i = 0; i < length; i++) {
      p += (char)payload[i];
    }
    for (auto d : m_devices) {
      if (d->m_commandTopic.length() > 0 && t == d->m_commandTopic) {
        d->m_handleCallback(p);
        break;
      }
    }
  }

  void Manager::m_updateAutoDiag(bool SkipTimer)
  {
    if (millis() - LastAutoDiagUpdate > m_AutoDiagInterval || SkipTimer) {
      for (auto d : m_devices) {
        if (d->m_diagType == AutoDiagType::RSSI) {
          String RSSI = String(WiFi.RSSI());
          d->setState(RSSI);
        }
        else if (d->m_diagType == AutoDiagType::UPTIME) {
          String uptimeValue = String(millis() / 1000);
          d->setState(uptimeValue);
        }
        else if (d->m_diagType == AutoDiagType::HEAP) {
          String freeHeapValue = String(ESP.getFreeHeap());
          d->setState(freeHeapValue);
        }
        else if (d->m_diagType == AutoDiagType::RESET) {
          esp_reset_reason_t r = esp_reset_reason();
          String reason = GetRestartString(r);
          d->setState(reason);
        }
      }
      LastAutoDiagUpdate = millis();
    }
  }

  const String Manager::GetRestartString(esp_reset_reason_t reason)
  {
    switch (reason) {
    case ESP_RST_UNKNOWN:
      return "Unknown";
    case ESP_RST_POWERON:
      return "Power-on";
    case ESP_RST_EXT:
      return "External reset";
    case ESP_RST_SW:
      return "Software reset";
    case ESP_RST_PANIC:
      return "Exception/panic reset";
    case ESP_RST_INT_WDT:
      return "Internal watchdog reset";
    case ESP_RST_TASK_WDT:
      return "Task watchdog reset";
    case ESP_RST_WDT:
      return "Other watchdog reset";
    case ESP_RST_DEEPSLEEP:
      return "Deep sleep reset";
    case ESP_RST_BROWNOUT:
      return "Brownout reset";
    case ESP_RST_SDIO:
      return "SDIO reset";
    default:
      return "Unknown";
    }
  }
}
