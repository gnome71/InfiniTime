#pragma once

#include <cstdint>
#include <string>
#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#undef max
#undef min

#define PRINTWATCH_SERVICE_UUID_BASE                                                                                                       \
  { 0xd0, 0x42, 0x19, 0x3a, 0x3b, 0x43, 0x23, 0x8e, 0xfe, 0x48, 0xfc, 0x78, 0x00, 0x00, 0x00, 0x00 }

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
      static constexpr uint8_t pwsId[2] = {0x02, 0x00};
      static constexpr uint8_t pwsHostCharId[2] = {0x01, 0x00};
      static constexpr uint8_t pwsExtruderCharId[2] = {0x02, 0x00};
      static constexpr uint8_t pwsBedCharId[2] = {0x03, 0x00};
      static constexpr uint8_t pwsDurationCharId[2] = {0x04, 0x00};

      ble_uuid128_t pwsUuid {.u = {.type = BLE_UUID_TYPE_128}, .value = PRINTWATCH_SERVICE_UUID_BASE};

      ble_uuid128_t pwsHostCharUuid {.u = {.type = BLE_UUID_TYPE_128}, .value = PRINTWATCH_SERVICE_UUID_BASE};
      ble_uuid128_t pwsExtruderCharUuid {.u = {.type = BLE_UUID_TYPE_128}, .value = PRINTWATCH_SERVICE_UUID_BASE};
      ble_uuid128_t pwsBedCharUuid {.u = {.type = BLE_UUID_TYPE_128}, .value = PRINTWATCH_SERVICE_UUID_BASE};
      ble_uuid128_t pwsDurationCharUuid {.u = {.type = BLE_UUID_TYPE_128}, .value = PRINTWATCH_SERVICE_UUID_BASE};

      struct ble_gatt_chr_def characteristicDefinition[5];
      struct ble_gatt_svc_def serviceDefinition[2];

      std::string hostname {"Host"};
      std::string extruderTemp {"0"};
      std::string bedTemp {"0"};
      std::string duration {"0"};
      
      Pinetime::System::SystemTask& m_system;
    };
  }
}
