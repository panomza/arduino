#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include "GenericMQTTClient.h"
#include "IPStack.h"
#include "Countdown.h"

template <int MAX_MQTT_PACKET_SIZE = 100, int MAX_MESSAGE_HANDLERS = 5>
class MQTTClient: public GenericMQTTClient<IPStack, Countdown, MAX_MQTT_PACKET_SIZE, MAX_MESSAGE_HANDLERS> {
public:
    MQTTClient(Client &client, unsigned int command_timeout_ms = 30000): ipstack(IPStack(client)),
            GenericMQTTClient<IPStack, Countdown, MAX_MQTT_PACKET_SIZE, MAX_MESSAGE_HANDLERS>(ipstack, command_timeout_ms) {}

    /** MQTT Connect - send an MQTT connect packet down the network and wait for a Connack
     *  The nework object must be connected to the network endpoint before calling this
     *  Default connect options are used
     *  @return success code -
     */
    virtual int connect();

    /** MQTT Connect - send an MQTT connect packet down the network and wait for a Connack
     *  The nework object must be connected to the network endpoint before calling this
     *  @param options - connect options
     *  @return success code -
     */
    virtual int connect(MQTTConnectOptions &options);



private:
    IPStack ipstack;
    void setMQTTString(MQTTString &dst, String const &src);
    void setMQTTWillOptions(MQTTPacket_willOptions &dst, const MQTTWillOptions &src);
    void setMQTTConnectData(MQTTPacket_connectData &dst, const MQTTConnectOptions &src);
};


template <int a, int b>
void MQTTClient<a, b>::setMQTTString(MQTTString &dst, const String &src) {
    dst.cstring = NULL;
    dst.lenstring.data = (char *) src.c_str();
    dst.lenstring.len = src.length();
}

template <int a, int b>
void MQTTClient<a, b>::setMQTTWillOptions(MQTTPacket_willOptions &dst, const MQTTWillOptions &src) {
    memcpy(dst.struct_id, src.id, sizeof(dst.struct_id));
    dst.struct_version = src.version;
    setMQTTString(dst.topicName, src.topic);
    setMQTTString(dst.message, src.payload);
    dst.retained = src.retained;
    dst.qos = src.qos;
}

template <int a, int b>
void MQTTClient<a, b>::setMQTTConnectData(MQTTPacket_connectData &dst, const MQTTConnectOptions &src) {
    memcpy(dst.struct_id, src.id, sizeof(dst.struct_id));
    dst.struct_version = src.version;
    dst.MQTTVersion = src.mqttVersion;
    setMQTTString(dst.clientID, src.clientID);
    dst.keepAliveInterval = src.keepAliveInterval;
    dst.cleansession = src.cleanSession;
    dst.willFlag = src.willFlag;
    setMQTTString(dst.username, src.username);
    setMQTTString(dst.password, src.password);
    setMQTTWillOptions(dst.will, src.will);
}

template <int a, int b>
int MQTTClient<a, b>::connect() {
    MQTTConnectOptions options;
    return this->connect(options);
}

template <int a, int b>
int MQTTClient<a, b>::connect(MQTTConnectOptions &options) {
    MQTTPacket_connectData data;
    setMQTTConnectData(data, options);
    return GenericMQTTClient<IPStack, Countdown, a, b>::connect(data);
}

#endif //MQTTCLIENT_H