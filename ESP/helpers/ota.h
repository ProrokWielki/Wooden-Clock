#ifndef OTA_H_
#define OTA_H_

#include <ArduinoOTA.h>

namespace ota
{

inline void initialize(const char * name = "hexagon_clock")
{
    ArduinoOTA.setHostname(name);

    ArduinoOTA.begin();
}

inline void handle()
{
    ArduinoOTA.handle();
}
}  // namespace ota

#endif /* OTA_H_ */
