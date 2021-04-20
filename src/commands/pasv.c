/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** pasv.c file
*/

#include <stdio.h>
#include "commands.h"
#include "sockets.h"
#include "sessions.h"

int pasv(session_t *config, char *argument)
{
    if (config->data_fd != -1) {
        // todo existing connection
    }
    int data_port = open_port(config->ctrl_fd + 256);  // todo calcul is off
    if (data_port < 0)
        return 1; // todo return error
    config->data_fd = data_port;

    // todo listen data_port ???
    // todo send ip & new port info
    int ip[4] = {127, 0, 0, 1};

    dprintf(config->ctrl_fd,
        "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", ip[0], ip[1],
        ip[2], ip[3], config->ctrl_fd, config->data_fd);

//    listen(data_port, );
//    accept()
    return 0;
}