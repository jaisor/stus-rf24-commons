#include "BaseMessage.h"

#include <Time.h>

CBaseMessage::CBaseMessage(const u_int8_t pipe)
: pipe(pipe) {
}

void CBaseMessage::populateJson(JsonDocument &json) {
  time_t now; 
  time(&now);
  char timeBuf[sizeof "2011-10-08T07:07:09Z"];
  strftime(timeBuf, sizeof timeBuf, "%FT%TZ", gmtime(&now));

  json.clear();
  json["timestamp_iso8601"] = String(timeBuf);
}