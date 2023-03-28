/*
 * ICP.h
 *
 *  Created on: Mar 28, 2023
 *      Author: argi1
 */

#ifndef IPC_H
#define IPC_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include "Timer.h"

/* This is the name that will be used by the server to create a channel and used by
 * the client to connect to the appropriated channel */
#define ATTACH_POINT "my_channel"

/* We specify the header as being at least a pulse */
/* All of your messages should start with this header */
/* This struct contains a type/subtype field as the first 4 bytes.
 * The type and subtype field can be used to identify the message that is being received.
 * This allows you to identify data which isn't destined for your server. */
typedef struct _pulse msg_header_t;

/* Our real data comes after the header */
typedef struct _my_data {
    msg_header_t hdr;
    double data;
} my_data_t;

class IPC {
    private:
        name_attach_t *attach;
        my_data_t msg;

    public:

        Timer timer;

        IPC();
        ~IPC();

        void* server_start_routine(void* );
        void* client_start_routine(void *);

        void startClient();
        void startServer();
        void execute_IPC();
};

#endif /* IPC_H */
