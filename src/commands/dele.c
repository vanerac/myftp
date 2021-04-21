/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** dele.c file
*/

#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sockets.h"
#include "sessions.h"

int dele(session_t *config, char *argument)
{
    // todo check auth
    char *direction = argument;
    char *buffer = calloc(strlen(config->working_dir) + strlen(direction) + 2,
        1);

    strcat(buffer, config->working_dir);
    if (buffer[strlen(buffer) - 1] != '/')
        strcat(&buffer[strlen(buffer) - 1], "/");
    strcat(&buffer[strlen(buffer)], direction);

    if (buffer[strlen(buffer)] != '/')
        buffer[strlen(buffer)] = '/';

    if (remove(buffer))
        write_socket(config->ctrl_fd,
            "550 Requested action not taken. File unavailable (e.g., file not found, no access).");
    else
        write_socket(config->ctrl_fd,
            "250 Requested file action okay, completed.");
    return 0;
}