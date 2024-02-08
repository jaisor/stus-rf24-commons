#include <ArduinoLog.h>

#include "RF24Message_VED_BATT.h"

CRF24Message_VED_BATT::CRF24Message_VED_BATT(const u_int8_t pipe, const r24_message_ved_batt_t msg)
: CBaseMessage(pipe), msg(msg) {  
  
  error = false;
  this->msg.id = MSG_VED_BATT_ID;
}

CRF24Message_VED_BATT::CRF24Message_VED_BATT(const u_int8_t pipe, const void* buf, const uint8_t length)
: CBaseMessage(pipe) { 
  if (length != getMessageLength()) {
    error = true;
    return;
  }
  memcpy(&msg, buf, length <= getMessageLength() ? length : getMessageLength());
  if (msg.id != MSG_VED_BATT_ID) {
    //Log.errorln(F("Message ID %i doesn't match MSG_VED_BATT_ID(%i)"), msg.id, MSG_VED_BATT_ID);
    memset(&msg, 0, getMessageLength());
    error = true;
  } else {
    error = false;
  }
}

const String CRF24Message_VED_BATT::getString() {
  char c[255];
  snprintf_P(c, 255, PSTR("[%u] (V=%0.2fV, VS=%0.2fV, I=%0.2fA, P=%0.2fV, SOC=%0.2f%%)"), pipe, 
        msg.b_voltage, msg.b_aux_voltage, msg.b_current, msg.b_power, msg.percent_charged/10.0);
  Log.verboseln(F("CRF24Message_VED_BATT::getString() : %s"), c);
  return String(c);
}

void CRF24Message_VED_BATT::populateJson(JsonDocument &json) {
  CBaseMessage::populateJson(json);
  json["message_id"] = msg.id;
  json["battery_voltage"] = msg.b_voltage;
  json["battery_aux_voltage"] = msg.b_aux_voltage;
  json["battery_current"] = msg.b_current;
  json["battery_power"] = msg.b_power;
  json["consumed_energy"] = msg.consumed_energy;
  json["percent_charged"] = msg.percent_charged;
  json["minutes_to_empty"] = msg.minutes_to_empty;
  json["alarm"] = msg.alarm;
}
