/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** help.c file
*/

#include <commands.h>
#include <sockets.h>
#include "sessions.h"

int help(session_t *config, char *argument)
{
    (void)argument;
    write_socket(config->ctrl_fd, "214 Help message.");
    return 0;
}