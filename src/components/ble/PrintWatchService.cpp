#include "PrintWatchService.h"
#include "systemtask/SystemTask.h"

int PrintWatchCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt, void* arg) {
  return static_cast<Pinetime::Controllers::PrintWatchService*>(arg)->OnPrintWatch(conn_handle, attr_handle, ctxt);
}

Pinetime::Controllers::PrintWatchService::PrintWatchService(Pinetime::System::SystemTask& system) : m_system(system) {
  // ServiceId: 00020000-78fc-48fe-8e23-433b3a1942d0
  pwsUuid.value[14] = pwsId[0];
  pwsUuid.value[15] = pwsId[1];

  // CharacteristicId hostname: 00020001-78fc-48fe-8e23-433b3a1942d0
  pwsHostCharUuid.value[12] = pwsHostCharId[0];
  pwsHostCharUuid.value[13] = pwsHostCharId[1];
  pwsHostCharUuid.value[14] = pwsId[0];
  pwsHostCharUuid.value[15] = pwsId[1];

  // CharacteristicId extruder temp.: 00020002-78fc-48fe-8e23-433b3a1942d0
  pwsExtruderCharUuid.value[12] = pwsExtruderCharId[0];
  pwsExtruderCharUuid.value[13] = pwsExtruderCharId[1];
  pwsExtruderCharUuid.value[14] = pwsId[0];
  pwsExtruderCharUuid.value[15] = pwsId[1];

  // CharacteristicId bed temp.: 00020003-78fc-48fe-8e23-433b3a1942d0
  pwsBedCharUuid.value[12] = pwsBedCharId[0];
  pwsBedCharUuid.value[13] = pwsBedCharId[1];
  pwsBedCharUuid.value[14] = pwsId[0];
  pwsBedCharUuid.value[15] = pwsId[1];

  // CharacteristicId duration: 00020004-78fc-48fe-8e23-433b3a1942d0
  pwsDurationCharUuid.value[12] = pwsDurationCharId[0];
  pwsDurationCharUuid.value[13] = pwsDurationCharId[1];
  pwsDurationCharUuid.value[14] = pwsId[0];
  pwsDurationCharUuid.value[15] = pwsId[1];

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
