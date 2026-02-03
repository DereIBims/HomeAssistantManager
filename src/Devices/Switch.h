#pragma once
#include "../HASSDevice.h"
#include "../HASSManager.h"

namespace HASSDevice {
    
    class Switch : public HASSDevice {
    private:
        String currentState = "OFF";
    public:
        Switch(HASSManager* mgr, String name);
        String getConfigJson() override;
        void setState(HASSState state);
        void onCommand(String& payload) override;
    };

}
