/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** pasv.c file
*/

#include "commands.h"
#include "sockets.h"

int pasv(session_t *config, char *argument)
{
    if (config->data_fd != -1) {
        // todo existing connection
    }
    int data_port = open_port(config->ctrl_fd + 256);
    if (data_port < 0)
        return 1; // todo return error
    config->data_fd = data_port;

    // todo send ip & new port info
    write_socket(config->ctrl_fd,
        "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).");

    return 0;
}