/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
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
 *    Benjamin Cabe - generic IPStack
 *******************************************************************************/

#ifndef IPSTACK_H
#define IPSTACK_H

#include <Arduino.h>
#include <Client.h>

class IPStack {
public:
//    IPStack() {}
    IPStack(Client &client) : client(&client) {

    }

    void setClient(Client &client) {
        this->client = &client;
    }

    int connect(char *hostname, uint16_t port) {
        return client->connect(hostname, port);
    }

    int connect(uint32_t hostname, uint16_t port) {
        return client->connect(hostname, port);
    }

    int read(unsigned char *buffer, size_t len, int timeout) {
        uint32_t interval = 10;  // all times are in milliseconds
        int total = 0, rc = -1;

        if (timeout < 30)
            interval = 2;
        while (client->available() < len && total < timeout) {
            delay(interval);
            total += interval;
        }
        if (client->available() >= len)
            rc = client->readBytes((char *) buffer, len);
        return rc;
    }

    int write(unsigned char *buffer, size_t len, unsigned long timeout) {
        client->setTimeout(timeout);
        return client->write(buffer, len);
    }

    int disconnect() {
        client->stop();
        return 0;
    }

private:

    Client *client;
};

#endif


