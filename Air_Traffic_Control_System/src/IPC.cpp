/*
 * IPC.cpp
 *
 *  Created on: Mar 28, 2023
 *      Author: argi1
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include "ICP.h"
#include "Timer.h"

using namespace std;

/* This is the name that will be used by the server to create a channel and used by
 * the client to connect to the appropriated channel */
#define ATTACH_POINT "my_channel"

/* We specify the header as being at least a pulse */
/* All of your messages should start with this header */
/* This struct contains a type/subtype field as the first 4 bytes.
 * The type and subtype field can be used to identify the message that is being received.
/ * This allows you to identify data which isn't destined for your server. */






void* IPC::server_start_routine(void*) {
    int rcvid;
    while (1) {
        // Wait for a message from a client
        rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
        if (rcvid == -1) {
            // Error occurred
            perror("MsgReceive");
            exit(EXIT_FAILURE);
        }

        // Print received data
        printf("Server received: %f\n", msg.data);

        // Send a response to the client
        msg.hdr.type = 0x01;
        msg.hdr.subtype = 0x00;
        MsgReply(rcvid, EOK, &msg, sizeof(msg));
    }
}

void* IPC::client_start_routine(void*) {
    int coid;
    struct _msg_info info;
    while (1) {
        // Connect to the server
        coid = name_open(ATTACH_POINT, 0);
        if (coid == -1) {
            // Error occurred
            perror("name_open");
            exit(EXIT_FAILURE);
        }

        // Send data to the server
        msg.hdr.type = 0x00;
        msg.hdr.subtype = 0x00;
        msg.data = rand() % 100;
        MsgSend(coid, &msg, sizeof(msg), &msg, sizeof(msg));

        // Print received data
        printf("Client received: %f\n", msg.data);

        // Close connection to the server
        name_close(coid);

        // Wait for the next activation

        timer.wait_next_activation();
    }
}

IPC::IPC() {
    // Initialize name attachment structure
    attach = name_attach(NULL, ATTACH_POINT, 0);
    if (attach == NULL) {
        perror("name_attach");
        exit(EXIT_FAILURE);
    }
}

IPC::~IPC() {
    // Detach name
    name_detach(attach, 0);
}

void IPC::startServer() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &server_start_routine, NULL);
    pthread_join(thread_id, NULL);
}

void IPC::startClient() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &client_start_routine, NULL);
}

void  execute_IPC(){
    IPC ipc;
    Timer timer(1, 0); // create timer with 1 second period
    ipc.timer = timer;
    ipc.startServer();

}
