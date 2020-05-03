#include <map>

#include <Arduino.h>

#include <ESP8266WiFi.h>

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
{"right", [](byte * payload, unsigned int length) { Serial.print("r"); }}};

void callback(char * topic, byte * payload, unsigned int length)
{
    Serial.print("a");
}

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
}

void loop()
{
    ota::handle();
    mqtt_.loop();
}
