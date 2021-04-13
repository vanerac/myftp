/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** noop.c file
*/

#include <commands.h>
#include "sockets.h"

int noop(session_t *config, char *argument)
{
    (void) argument;
    write_socket(config->ctrl_fd, "200 Command okay.");
    return 0;
}