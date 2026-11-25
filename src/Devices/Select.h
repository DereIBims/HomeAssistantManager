#pragma once
#include "../Device.h"
#include <initializer_list>
#include <vector>

namespace HA {
  class SelectBase : public Device, public CallbackMixin<const String &> {
public:
    SelectBase(Manager *mgr, const char *name, std::initializer_list<const char *> options);
    bool setValue(const String &VALUE);

private:
    void configureEntity(JsonObject config) override;
    void m_handleCallback(String payload) override;
    bool isValidOption(const String &value) const;
    std::vector<String> m_options;
  };

  class Select {
public:
    class Generic : public SelectBase {
  public:
      Generic(Manager *mgr, const char *name, std::initializer_list<const char *> options);
    };
  };
}
