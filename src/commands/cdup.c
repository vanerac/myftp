/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** cdup.c file
*/

#include <string.h>
#include <stdlib.h>
#include "sockets.h"
#include "commands.h"

int cdup(session_t *config, char *argument)
{
    if (!config->logged)
        return 0; // todo error message
    (void) argument;
    char *buffer = config->working_dir;
    if (!rindex(buffer, '/') || rindex(buffer, '/') == index(buffer, '/')) {
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
        return 0;
    }
    if (buffer[strlen(buffer) - 1] == '/' && strlen(buffer) > 1) {
        buffer[strlen(buffer) - 1] = '\0';
    }
    char *ptr = rindex(buffer, '/');

    char *new_path = strndup(buffer,
        (ptr - config->working_dir) > 0 ? ptr - config->working_dir : 1);
    free(config->working_dir);
    config->working_dir = new_path;
    write_socket(config->ctrl_fd, "200 Command okay.");
    return 0;
}