/*******************************************************************************
 * Copyright (c) 2014 IBM Corp. and others
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *   http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *    Benjamin Cabe - adapt to IPStack, and add Yun instructions
 *******************************************************************************/

#define MQTTCLIENT_QOS2 1

#include <WiFi.h>
#include <OxMqtt.h>

// your network name also called SSID
char ssid[] = "dolink";
// your network password
char password[] = "king8888";

char printbuf[100];

int arrivedcount = 0;

void messageArrived(MQTTMessage &md) {
    MQTTPacket &message = md.packet;

    sprintf(printbuf, "<- NO: %d, qos: %d, retained: %d, dup: %d, packetid: %d\n",
            ++arrivedcount, message.qos, message.retained, message.dup, message.id);
    Serial.print(printbuf);
    sprintf(printbuf, "   Payload: %s\n", (char *) message.payload);
    Serial.print(printbuf);
}

WiFiClient c; // replace by a YunClient if running on a Yun
IPStack ipstack(c);
MQTTClient<> client(ipstack);

const char *topic = "arduino-sample";

void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void setupWiFi() {
    // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, password);
    while ( WiFi.status() != WL_CONNECTED) {
        // print dots while we wait to connect
        Serial.print(".");
        delay(300);
    }

    Serial.println("\nYou're connected to the network");
    Serial.println("Waiting for an ip address");

    while (WiFi.localIP() == INADDR_NONE) {
        // print dots while we wait for an ip addresss
        Serial.print(".");
        delay(300);
    }

    Serial.println("\nIP Address obtained");
    printWifiStatus();
}

void connect() {
    char hostname[] = "iot.eclipse.org";
    int port = 1883;
    sprintf(printbuf, "Connecting to %s:%d\n", hostname, port);
    Serial.print(printbuf);
    int rc = ipstack.connect(hostname, port);
    if (rc != 1) {
        sprintf(printbuf, "rc from TCP connect is %d\n", rc);
        Serial.print(printbuf);
    }

    Serial.println("MQTT connecting");
    MQTTConnectOptions options;
    options.version = 3;
    options.clientID = "arduino-sample";
    rc = client.connect(options);
    if (rc != 0) {
        sprintf(printbuf, "rc from MQTT connect is %d\n", rc);
        Serial.print(printbuf);
    }
    Serial.println("MQTT connected");

    rc = client.subscribe(topic, QOS2, messageArrived);
    if (rc != 0) {
        sprintf(printbuf, "rc from MQTT subscribe is %d\n", rc);
        Serial.print(printbuf);
    }
    Serial.println("MQTT subscribed");
}

void setup() {
    Serial.begin(115200);

    Serial.println("MQTT Hello example");
    setupWiFi();

    Serial.println("Connecting to mqtt server ...");
    connect();
}

void loop() {
    if (!client.isConnected())
        connect();

    MQTTPacket message;

    arrivedcount = 0;

    // Send and receive QoS 0 message
    char buf[100];
    sprintf(buf, "Hello World! QoS 0 message");
    Serial.print("-> ");
    Serial.println(buf);
    message.qos = QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void *) buf;
    message.length = strlen(buf) + 1;
    int rc = client.publish(topic, message);
    while (arrivedcount == 0)
        client.yield(1000);

    // Send and receive QoS 1 message
    sprintf(buf, "Hello World!  QoS 1 message");
    Serial.print("-> ");
    Serial.println(buf);
    message.qos = QOS1;
    message.length = strlen(buf) + 1;
    rc = client.publish(topic, message);
    while (arrivedcount == 1)
        client.yield(1000);

    // Send and receive QoS 2 message
    sprintf(buf, "Hello World!  QoS 2 message");
    Serial.print("-> ");
    Serial.println(buf);
    message.qos = QOS2;
    message.length = strlen(buf) + 1;
    rc = client.publish(topic, message);
    while (arrivedcount == 2)
        client.yield(1000);

    delay(2000);
}
