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

static int error_check(session_t *config)
{
    if (!config->logged) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
        return 1;
    }
    if (config->data_fd != -1) {
        write_socket(config->ctrl_fd, "125 Data connection already open");
        return 1;
    }
    return 0;
}

int pasv(session_t *config, char *argument)
{
    (void) argument;
    if (error_check(config))
        return 0;
    int data_port = open_port(config->ctrl_fd * 256 + config->ctrl_fd);
    if (data_port < 0) {
        write_socket(config->ctrl_fd, "425 Retry later bruh");
        return 0;
    }
    dprintf(config->ctrl_fd,
        "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n", config->ctrl_fd,
        config->ctrl_fd);
    listen(data_port, 1);
    struct sockaddr_in client;
    unsigned long int length = sizeof(client);
    config->data_fd = accept(data_port, (struct sockaddr *) &client,
        (socklen_t *) &length);
    return 0;
}