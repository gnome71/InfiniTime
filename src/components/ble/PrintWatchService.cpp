#include "PrintWatchService.h"
#include "systemtask/SystemTask.h"

namespace {
  // 0000yyxx-78fc-48fe-8e23-433b3a1942d0
  constexpr ble_uuid128_t CharUuid(uint8_t x, uint8_t y) {
    return ble_uuid128_t{
      .u = {.type = BLE_UUID_TYPE_128},
      .value =  { 0xd0, 0x42, 0x19, 0x3a, 0x3b, 0x43, 0x23, 0x8e, 0xfe, 0x48, 0xfc, 0x78, 0x00, 0x00, x, y }
    };
  }

  // 00000000-78fc-48fe-8e23-433b3a1942d0
  constexpr ble_uuid128_t BaseUuid() {
    return CharUuid(0x02, 0x00);
  }

  constexpr ble_uuid128_t pwsUuid {BaseUuid()};

  constexpr ble_uuid128_t pwsHostCharUuid {CharUuid(0x01, 0x00)};
  constexpr ble_uuid128_t pwsExtruderCharUuid {CharUuid(0x02, 0x00)};
  constexpr ble_uuid128_t pwsBedCharUuid {CharUuid(0x03, 0x00)};
  constexpr ble_uuid128_t pwsDurationCharUuid {CharUuid(0x04, 0x00)};

  int PrintWatchCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt, void* arg) {
    return static_cast<Pinetime::Controllers::PrintWatchService*>(arg)->OnPrintWatch(conn_handle, attr_handle, ctxt);
  }
}

Pinetime::Controllers::PrintWatchService::PrintWatchService(Pinetime::System::SystemTask& system) : m_system(system) {
  characteristicDefinition[0] = {.uuid = &pwsHostCharUuid.u,
                                 .access_cb = PrintWatchCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ};
  characteristicDefinition[1] = {.uuid = &pwsExtruderCharUuid.u,
                                 .access_cb = PrintWatchCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ};
  characteristicDefinition[2] = {.uuid = &pwsBedCharUuid.u,
                                 .access_cb = PrintWatchCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ};
  characteristicDefinition[3] = {.uuid = &pwsDurationCharUuid.u,
                                 .access_cb = PrintWatchCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ};
  characteristicDefinition[4] = {0};

  serviceDefinition[0] = {
    .type = BLE_GATT_SVC_TYPE_PRIMARY, .uuid = &pwsUuid.u, .characteristics = characteristicDefinition};
  serviceDefinition[1] = {0};
}

void Pinetime::Controllers::PrintWatchService::Init() {
  uint8_t res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}

int Pinetime::Controllers::PrintWatchService::OnPrintWatch(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt) {
  if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
    size_t notifSize = OS_MBUF_PKTLEN(ctxt->om);
    char data[notifSize + 1];
    data[notifSize] = '\0';
    os_mbuf_copydata(ctxt->om, 0, notifSize, data);
    char* s = &data[0];
    if (ble_uuid_cmp(ctxt->chr->uuid, &pwsHostCharUuid.u) == 0) {
      hostname = s;
    } else if (ble_uuid_cmp(ctxt->chr->uuid, &pwsExtruderCharUuid.u) == 0) {
      extruderTemp = s;
    } else if (ble_uuid_cmp(ctxt->chr->uuid, &pwsBedCharUuid.u) == 0) {
      bedTemp = s;
    } else if (ble_uuid_cmp(ctxt->chr->uuid, &pwsDurationCharUuid.u) == 0) {
      duration = s;
    }
  }
  return 0;
}

std::string Pinetime::Controllers::PrintWatchService::getExtruderTemp() const {
  return extruderTemp;
}

std::string Pinetime::Controllers::PrintWatchService::getBedTemp() const {
  return bedTemp;
}

std::string Pinetime::Controllers::PrintWatchService::getHost() const {
  return hostname;
}

std::string Pinetime::Controllers::PrintWatchService::getDuration() const {
  return duration;
}
