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

        lv_obj_t *extruderArc, *extruderValueLabel, *extruderLabel; 
        lv_obj_t *bedArc, *bedValueLabel, *bedLabel;
        lv_obj_t *hostLabel;
        lv_obj_t *etaLabel, *etaValueLabel;
        lv_obj_t *durationBar;

        const char *hostName;
        uint16_t extruderTemp;
        uint8_t bedTemp;
        uint16_t eta;
      };
    }
  }
}