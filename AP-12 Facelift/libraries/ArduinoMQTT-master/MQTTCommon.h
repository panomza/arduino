/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Ian Craggs - fix for bug 458512 - QoS 2 messages
 *    Ian Craggs - fix for bug 460389 - send loop uses wrong length
 *******************************************************************************/

#ifndef MQTTCOMMON_T
#define MQTTCOMMON_T

#include "Arduino.h"
#include "FP.h"
#include "utility/MQTTPacket.h"
#include "stdio.h"
#include "MQTTLogging.h"

//#define MQTT_DEBUG

#if !defined(MQTTCLIENT_QOS1)
#define MQTTCLIENT_QOS1 1
#endif
#if !defined(MQTTCLIENT_QOS2)
#define MQTTCLIENT_QOS2 0
#endif

enum MQTTQoS {
    QOS0, QOS1, QOS2
};

// all failure return codes must be negative
enum MQTTReturnCode {
    BUFFER_OVERFLOW = -2, FAILURE = -1, SUCCESS = 0
};

struct MQTTPacket {
    enum MQTTQoS qos;
    bool retained;
    bool dup;
    unsigned short id;
    void *payload;
    size_t length;
};


struct MQTTMessage {
    MQTTMessage(MQTTString &aTopic, struct MQTTPacket &aPacket) : topic(aTopic), packet(aPacket) {}

    MQTTString topic;
    struct MQTTPacket &packet;
};


class MQTTPacketId {
public:
    MQTTPacketId() {
        next = 0;
    }

    int getNext() {
        return next = (next == MAX_PACKET_ID) ? 1 : ++next;
    }

private:
    static const int MAX_PACKET_ID = 65535;
    int next;
};

class MQTTWillOptions {
public:
    MQTTWillOptions(): id({'M', 'Q', 'T', 'W'}), version(0), topic(""), payload(""), retained(0), qos(0) {}


    /** The eyecatcher for this structure.  must be MQTW. */
    char id[4];

    /** The version number of this structure.  Must be 0 */
    int version;

    /** The LWT topic to which the LWT message will be published. */
    String topic;

    /** The LWT payload. */
    String payload;

    /**
      * The retained flag for the LWT message (see MQTTAsync_message.retained).
      */
    byte retained;
    /**
      * The quality of service setting for the LWT message (see
      * MQTTAsync_message.qos and @ref qos).
      */
    byte qos;

};

class MQTTConnectOptions {
public:
    MQTTConnectOptions(): id({'M', 'Q', 'T', 'C'}), version(0), mqttVersion(4), clientID(""),
                          keepAliveInterval(60), cleanSession(1), willFlag(0), username(""), password("") {}

    /** The eyecatcher for this structure.  must be MQTC. */
    char id[4];

    /** The version number of this structure.  Must be 0 */
    int version;

    /** Version of MQTT to be used.  3 = 3.1 4 = 3.1.1
      */
    unsigned char mqttVersion;
    String clientID;
    unsigned short keepAliveInterval;
    unsigned char cleanSession;
    unsigned char willFlag;
    MQTTWillOptions will;
    String username;
    String password;

};


#endif
