#include <ArduinoLog.h>
#include <Arduino.h>

#include "RF24Message.h"

CRF24Message::CRF24Message(const u_int8_t pipe, const r24_message_uvthp_t msg)
: CBaseMessage(pipe), msg(msg) {  
  
  error = false;
  this->msg.id = MSG_UVTHP_ID;
}

CRF24Message::CRF24Message(const u_int8_t pipe, const void* buf, const uint8_t length)
: CBaseMessage(pipe) { 
  if (length != getMessageLength()) {
    error = true;
    return;
  }
  memcpy(&msg, buf, length <= getMessageLength() ? length : getMessageLength());
  if (msg.id != MSG_UVTHP_ID) {
    //Log.errorln(F("Message ID %i doesn't match MSG_UVTHP_ID(%i)"), msg.id, MSG_UVTHP_ID);
    memset(&msg, 0, getMessageLength());
    error = true;
  } else {
    error = false;
  }
}

const String CRF24Message::getString() {
  char c[255];
  snprintf_P(c, 255, PSTR("[%u] (V=%0.2fV, T=%0.2fC, H=%0.2f%%, BP=%0.2fKPa U=%0.2fsec) ERR=%i"), pipe, 
        msg.voltage, msg.temperature, msg.humidity, msg.baro_pressure/1000.0, (float)(msg.uptime)/1000.0, msg.error);
  Log.verboseln(F("CRF24Message::getString() : %s"), c);
  return String(c);
}

void CRF24Message::populateJson(JsonDocument &json) {
  CBaseMessage::populateJson(json);
  json["message_id"] = MSG_UVTHP_ID;
  json["uptime_millis"] = msg.uptime;
  json["voltage"] = msg.voltage;
  json["temperature"] = msg.temperature*9.0/5.0 + 32.0;
  json["temperature_unit"] = F("Fahrenheit"); // TODO: make configurable
  json["humidity"] = msg.humidity;
  json["humidity_unit"] = "percent";
  json["barometric_pressure"] = msg.baro_pressure;
  json["barometric_pressure_unit"] = "Pascal";
  json["error"] = msg.error;
}