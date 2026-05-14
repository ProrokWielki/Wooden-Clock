#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <pb_encode.h>
#include <time.h>

#include "time_msg.pb.h"

#include <functional>
#include <map>
#include <string>

#include "config/mqtt_config.h"
#include "config/wifi_config.h"

#include "helpers/mqtt.h"
#include "helpers/ota.h"

WiFiClient wifi_;
PubSubClient mqtt_(mqtt::server_ip, mqtt::server_port, wifi_);

std::map<std::string, std::function<void(byte * payload, unsigned int length)>> handle_topic{
{"up", [](byte * payload, unsigned int length) { Serial.print("u"); }},
{"down", [](byte * payload, unsigned int length) { Serial.print("d"); }},
{"left", [](byte * payload, unsigned int length) { Serial.print("l"); }},
{"reset", [](byte * payload, unsigned int length) { Serial.print("w"); }},
{"right", [](byte * payload, unsigned int length) { Serial.print("r"); }},
{"test",
 [](byte * payload, unsigned int length) {
     time_t now = time(nullptr);
     struct tm * timeinfo = localtime(&now);

     time_msg msg = time_msg_init_zero;
     msg.hours = timeinfo->tm_hour;
     msg.minutes = timeinfo->tm_min;
     msg.seconds = timeinfo->tm_sec;
     uint8_t buffer[time_msg_size];
     pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
     pb_encode(&stream, time_msg_fields, &msg);
     Serial.write(buffer, stream.bytes_written);
 }},
};

const char * TZ_INFO = "CET-1CEST,M3.5.0/2,M10.5.0/3";

void setup()
{
    Serial.begin(500000);

    ota::initialize();

    WiFi.hostname(wifi::hostname);
    WiFi.begin(wifi::ssid, wifi::password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    while (not mqtt_.connect(mqtt::client_id))
    {
        delay(500);
    }

    mqtt_.setCallback([](char * topic, byte * payload, unsigned int length) { handle_topic[topic](payload, length); });
    mqtt::subscribe(mqtt_, handle_topic);

    configTime(TZ_INFO, "tempus1.gum.gov.pl", "pl.pool.ntp.org");

    Serial.println("----- setup done --------");
}

void loop()
{
    ota::handle();
    mqtt_.loop();
}
