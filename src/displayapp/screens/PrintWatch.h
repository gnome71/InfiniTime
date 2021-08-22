#pragma once

#include "systemtask/SystemTask.h"
#include <string>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class PrintWatch : public Screen {
        public:
          PrintWatch(DisplayApp* app, System::SystemTask& systemTask);
          ~PrintWatch() override;
          bool Refresh() override;

        private:
          System::SystemTask& systemTask;

        bool printwatchStarted = false;

        lv_obj_t *extruderLabel, *extruderValueLabel; 
        lv_obj_t *bedLabel, *bedValueLabel;
        lv_obj_t *hostLabel, *hostValueLabel;
        lv_obj_t *etaLabel, *etaValueLabel;
        lv_obj_t *durationBar;

        uint16_t extruderTemp;
        uint8_t bedTemp;
        std::string hostName;
      };
    }
  }
}