#pragma once

#include <FreeRTOS.h>
#include <lvgl/src/lv_core/lv_obj.h>
#include <string>
#include "Screen.h"

namespace Pinetime {
  namespace Controllers {
    class PrintWatchService;
  }

  namespace Applications {
    namespace Screens {
      class PrintWatch : public Screen {
        public:
          PrintWatch(DisplayApp* app, Pinetime::Controllers::PrintWatchService& printwatch);
          ~PrintWatch() override;
          bool Refresh() override;

        private:
          bool printwatchStarted = false;
  
          lv_obj_t *extruderArc, *extruderValueLabel, *extruderLabel; 
          lv_obj_t *bedArc, *bedValueLabel, *bedLabel;
          lv_obj_t *hostLabel;
          //lv_obj_t *etaLabel, *etaValueLabel;
          lv_obj_t *durationBar;
  
          Pinetime::Controllers::PrintWatchService& printwatchService;
          
          std::string hostName;
          std::string extruderTemp;
          std::string bedTemp;
          std::string eta;
      };
    }
  }
}