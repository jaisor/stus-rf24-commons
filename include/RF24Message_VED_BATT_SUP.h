#pragma once

#include "BaseMessage.h"

class CRF24Message_VED_BATT_SUP: public CBaseMessage {
private:
  r24_message_ved_batt_sup_t msg;
  bool error;
public:
  CRF24Message_VED_BATT_SUP(const u_int8_t pipe, const r24_message_ved_batt_sup_t msg);
  CRF24Message_VED_BATT_SUP(const u_int8_t pipe, const void* buf, const uint8_t length);
  virtual ~CRF24Message_VED_BATT_SUP() {}

  virtual const void* getMessageBuffer() { return &msg; } 
  virtual const uint8_t getMessageLength() { return sizeof(r24_message_ved_batt_sup_t); }
  virtual const bool isError() { return error; }
  virtual const String getString();
  virtual const uint8_t getId() { return msg.id; }
};
