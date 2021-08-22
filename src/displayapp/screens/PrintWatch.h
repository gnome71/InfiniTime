#pragma once

#include "systemtask/SystemTask.h"

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
      };
    }
  }
}