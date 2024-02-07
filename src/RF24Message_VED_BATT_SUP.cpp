#include <ArduinoLog.h>

#include "RF24Message_VED_BATT_SUP.h"

CRF24Message_VED_BATT_SUP::CRF24Message_VED_BATT_SUP(const u_int8_t pipe, const r24_message_ved_batt_t msg)
: CBaseMessage(pipe), msg(msg) {  
  
  error = false;
  this->msg.id = MSG_VED_BATT_ID;
}

CRF24Message_VED_BATT_SUP::CRF24Message_VED_BATT_SUP(const u_int8_t pipe, const void* buf, const uint8_t length)
: CBaseMessage(pipe) { 
  if (length != getMessageLength()) {
    error = true;
    return;
  }
  memcpy(&msg, buf, length <= getMessageLength() ? length : getMessageLength());
  if (msg.id != MSG_VED_MPPT_ID) {
    //Log.errorln(F("Message ID %i doesn't match MSG_VED_MPPT_ID(%i)"), msg.id, MSG_VED_MPPT_ID);
    memset(&msg, 0, getMessageLength());
    error = true;
  } else {
    error = false;
  }
}

const String CRF24Message_VED_BATT_SUP::getString() {
  char c[255];
  snprintf_P(c, 255, PSTR("[%u] (VMin=%0.2fV, VMax=%0.2fV, EC=%0.2fAh, EDC=%0.2f%Ah)"), pipe, 
        msg.b_voltage_min, msg.b_voltage_max, msg.energy_charged, msg.energy_discharged);
  Log.verboseln(F("CRF24Message_VED_BATT_SUP::getString() : %s"), c);
  return String(c);
}

void CRF24Message_VED_BATT_SUP::populateJson(JsonDocument &json) {
  CBaseMessage::populateJson(json);
  json["message_id"] = MSG_VED_INV_ID;
  json["discharge_last"] = msg.discharge_last;
  json["charge_cycles"] = msg.charge_cycles;
  json["battery_voltage_min"] = msg.b_voltage_min;
  json["battery_voltage_min"] = msg.b_voltage_max;
  json["battery_aux_voltage_min"] = msg.b_aux_voltage_min;
  json["battery_aux_voltage_min"] = msg.b_aux_voltage_max;
  json["energy_charged"] = msg.energy_charged;
  json["energy_discharged"] = msg.energy_discharged;
}
