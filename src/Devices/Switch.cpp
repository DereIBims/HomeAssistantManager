/*

#include "Switch.h"

namespace HASSDevice {

  Switch::Switch(HASSManager *mgr, String name) : HASSDevice(mgr, name, "switch") {
    commandTopic = "homeassistant/switch/" + deviceId + "/set";
  }

  String Switch::getConfigJson() {
    String json = "{\"name\":\"" + name + "\", \"state_topic\":\"" + stateTopic + "\", \"command_topic\":\"" + commandTopic + "\", \"device\":{\"ids\":[\"" + manager->deviceId + "\"]";
    if (manager->deviceName.length() > 0) {
      json += ", \"name\":\"" + manager->deviceName + "\"";
    }
    if (manager->manufacturer.length() > 0) {
      json += ", \"mf\":\"" + manager->manufacturer + "\"";
    }
    if (manager->model.length() > 0) {
      json += ", \"mdl\":\"" + manager->model + "\"";
    }
    if (manager->swVersion.length() > 0) {
      json += ", \"sw\":\"" + manager->swVersion + "\"";
    }
    if (manager->serialNumber.length() > 0) {
      json += ", \"sn\":\"" + manager->serialNumber + "\"";
    }
    json += "}}";
    return json;
  }

  void Switch::setState(HASSState state) {
    currentState = (state == HASSState::ON ? "ON" : "OFF");
    publishState(currentState);
  }

  void Switch::onCommand(String payload) {
    HASSCommand cmd;
    cmd.state = (payload == "ON" ? HASSState::ON : HASSState::OFF);
    if (payload == "ON") {
      currentState = "ON";
    } else if (payload == "OFF") {
      currentState = "OFF";
    }
    publishState(currentState);
    if (commandCallback) {
      commandCallback(cmd);
    }
  }

}

*/