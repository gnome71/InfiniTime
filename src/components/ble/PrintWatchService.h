#pragma once

#include <cstdint>
#include <string>
#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#undef max
#undef min

namespace Pinetime {
  namespace System {
    class SystemTask;
  }
  namespace Controllers {
    class PrintWatchService {
    public:
      PrintWatchService(Pinetime::System::SystemTask& system);
      void Init();

      int OnPrintWatch(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt);
      std::string getHost() const;
      std::string getExtruderTemp() const;
      std::string getBedTemp() const;
      std::string getDuration() const;

    private:
      struct ble_gatt_chr_def characteristicDefinition[5];
      struct ble_gatt_svc_def serviceDefinition[2];

      std::string hostname {"None"};
      std::string extruderTemp {"0"};
      std::string bedTemp {"0"};
      std::string duration {"0"};
      
      Pinetime::System::SystemTask& m_system;
    };
  }
}
