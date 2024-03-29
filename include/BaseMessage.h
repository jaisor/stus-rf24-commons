#pragma once

#include <ArduinoJson.h>
#include <Arduino.h>

// Message Uptime-Voltage-Temperature-Humidity-BarometricPressure
#define MSG_UVTHP_ID 1
typedef struct r24_message_uvthp_t {
  uint8_t id; // message id
  uint32_t uptime;
  float voltage;
  float temperature;
  float humidity;
  float baro_pressure;
  uint8_t error;
  uint8_t pad[7];
} _r24_message_uvthp_t;

#define MSG_VED_INV_ID 2
typedef struct r24_message_ved_inv_t {
  uint8_t id;             // message id
  //
  float b_voltage;        // V
  float ac_current;       // A - when > 0, the battery is being charged, < 0 the battery is being
  float ac_voltage;       // V
  float ac_va_power;      // VA
  uint8_t current_state;
  int8_t mode;
  uint8_t off_reason;
  uint8_t alarm;
  uint8_t warning;
  //
  float temperature;      // C
} _r24_message_ved_inv_t;

#define MSG_VED_MPPT_ID 3
typedef struct r24_message_ved_mppt_t {
  uint8_t id;             // message id
  //
  float b_voltage;        // V
  float b_current;        // A - when > 0, the battery is being charged, < 0 the battery is being
  float p_voltage;        // V
  float p_power;          // W
  uint8_t current_state;
  uint8_t mppt;
  uint8_t off_reason;
  uint8_t error;
  //
  uint16_t today_yield;      // 0.01*Wh
  uint16_t today_max_power;  // 0.01*Wh
  //
  float temperature;      // C
} _r24_message_ved_mppt_t;

#define MSG_VED_BATT_ID 4
typedef struct r24_message_ved_batt_t {
  uint8_t id;             // message id
  //
  float b_voltage;            // V
  float b_aux_voltage;        // V
  float b_current;            // A - when > 0, the battery is being charged, < 0 the battery is being
  int16_t b_power;            // W
  float consumed_energy;      // Ah
  uint16_t percent_charged;   // *0.1 % 0 - 100
  uint16_t minutes_to_empty;
  uint8_t alarm; 
} _r24_message_ved_batt_t;

#define MSG_VED_BATT_SUP_ID 5 // Supplemental
typedef struct r24_message_ved_batt_sup_t {
  uint8_t id;                 // message id
  //
  float discharge_last;       // Ah
  uint16_t charge_cycles;
  //
  float b_voltage_min;        // V
  float b_aux_voltage_min;    // V
  //
  float energy_charged;       // Wh
  float energy_discharged;    // Wh
  //
  float temperature;          // C
} _r24_message_ved_batt_sup_t;

typedef enum stus_error_codes {
  NoError = 0,
  VEDirectCommFail = 1,
  TempSensorFail = 2,
  BattSensorFail = 3
} _stus_error_codes;

class CBaseMessage {

protected:
    unsigned long tMillis;
    const u_int8_t pipe;

public:
	CBaseMessage(const u_int8_t pipe);
  virtual ~CBaseMessage() {}
  
  const uint8_t getPipe() { return pipe; };
  virtual const String getString() { return String(""); }
  virtual const uint8_t getId() = 0;
  virtual const bool isError() { return false; }
  virtual const void* getMessageBuffer() = 0; 
  virtual const uint8_t getMessageLength() = 0; 
  virtual void populateJson(JsonDocument &json);
};
