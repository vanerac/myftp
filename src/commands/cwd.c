/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** cwd.c file
*/

#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include "sockets.h"
#include "commands.h"
#include "sessions.h"

int cwd(session_t *config, char *argument)
{
    char *direction = argument;

    char *buffer = calloc(strlen(config->working_dir) + strlen(direction) + 2,
        1);
    strcat(buffer, config->working_dir);
    if (buffer[strlen(buffer) - 1] != '/')
        strcat(&buffer[strlen(buffer) - 1], "/");
    strcat(&buffer[strlen(buffer)], direction);

    if (buffer[strlen(buffer)] != '/')
        buffer[strlen(buffer)] = '/';

    DIR *dir = opendir(buffer);
    if (dir) {
        write_socket(config->ctrl_fd,
            "250 Requested file action okay, completed.");
        free(config->working_dir);
        config->working_dir = buffer;
    } else
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
    closedir(dir);
    return 0;
}