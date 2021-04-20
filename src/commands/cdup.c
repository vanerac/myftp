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
    (void) argument;
    char *ptr = strchr(config->working_dir, '/');

    if (!ptr || ptr == config->working_dir) {
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
        return 1;
    }

    char *new_path = strndup(config->working_dir, config->working_dir - ptr);
    free(config->working_dir);
    config->working_dir = new_path;
    write_socket(config->ctrl_fd, "200 Command okay.");
    return 0;
}