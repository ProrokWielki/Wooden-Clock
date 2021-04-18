#ifndef MQTT_H_
#define MQTT_H_

#include <PubSubClient.h>

namespace mqtt
{

void subscribe(PubSubClient & mqtt, const std::map<std::string, std::function<void(byte * payload, unsigned int length)>> & topics_to_subscribe)
{
    for (const auto & topic : topics_to_subscribe)
    {
        mqtt.subscribe(topic.first.c_str());
    }
}

}  // namespace mqtt

#endif /* MQTT_H_ */
