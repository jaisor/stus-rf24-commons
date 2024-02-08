#include <ArduinoLog.h>

#include "RF24Message_VED_INV.h"

CRF24Message_VED_INV::CRF24Message_VED_INV(const u_int8_t pipe, const r24_message_ved_inv_t msg)
: CBaseMessage(pipe), msg(msg) {  
  
  error = false;
  this->msg.id = MSG_VED_INV_ID;
}

CRF24Message_VED_INV::CRF24Message_VED_INV(const u_int8_t pipe, const void* buf, const uint8_t length)
: CBaseMessage(pipe) { 
  if (length != getMessageLength()) {
    error = true;
    return;
  }
  memcpy(&msg, buf, length <= getMessageLength() ? length : getMessageLength());
  if (msg.id != MSG_VED_INV_ID) {
    //Log.errorln(F("Message ID %i doesn't match MSG_VED_INV_ID(%i)"), msg.id, MSG_VED_INV_ID);
    memset(&msg, 0, getMessageLength());
    error = true;
  } else {
    error = false;
  }
}

const String CRF24Message_VED_INV::getString() {
  char c[255];
  snprintf_P(c, 255, PSTR("[%u] (V=%0.2fV, ACI=%0.2fA, ACV=%0.2fV, ACVA=%0.2fW T=%0.2fC)"), pipe, 
        msg.b_voltage, msg.ac_current, msg.ac_voltage, msg.ac_va_power, msg.temperature);
  Log.verboseln(F("CRF24Message_VED_INV::getString() : %s"), c);
  return String(c);
}

void CRF24Message_VED_INV::populateJson(JsonDocument &json) {
  CBaseMessage::populateJson(json);
  json["message_id"] = msg.id;
  json["battery_voltage"] = msg.b_voltage;
  json["ac_current"] = msg.ac_current;
  json["ac_voltage"] = msg.ac_voltage;
  json["ac_va_power"] = msg.ac_va_power;
  json["current_state"] = msg.current_state;
  json["mode"] = msg.mode;
  json["off_reason"] = msg.off_reason;
  json["alarm"] = msg.alarm;
  json["warning"] = msg.warning;
  json["temperature"] = msg.temperature*9.0/5.0 + 32.0;
  json["temperature_unit"] = F("Fahrenheit"); // TODO: make configurable
}