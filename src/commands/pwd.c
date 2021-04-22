/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** pwd.c file
*/

#include <stdio.h>
#include "sockets.h"
#include "commands.h"
#include "sessions.h"

int pwd(session_t *config, char *argument)
{
    if (!config->logged) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
        return 0;
    }
    (void) argument;
    dprintf(config->ctrl_fd, "257 \"%s\"\r\n", config->working_dir);
    return 0;
}