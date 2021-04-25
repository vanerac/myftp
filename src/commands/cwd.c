/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** cwd.c file
*/

#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include <tools.h>
#include "sockets.h"
#include "commands.h"
#include "sessions.h"

static int error_check(session_t *config, char *argument)
{
    if (!config->logged) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
        return 1;
    }
    if (!argument) {
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
        return 1;
    }
    return 0;
}

int cwd(session_t *config, char *argument)
{
    char *buffer;
    if (error_check(config, argument))
        return 0;
    if (argument[0] == '/')
        buffer = strdup(argument);
    else
        buffer = append_path(config->working_dir, argument);
    if (buffer[strlen(buffer) - 1] != '/')
        strcat(&buffer[strlen(buffer) - 1], "/");
    DIR *dir = opendir(buffer);
    if (dir) {
        write_socket(config->ctrl_fd, "250 Requested file action okay.");
        free(config->working_dir);
        config->working_dir = buffer;
    } else
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
    closedir(dir);
    return 0;
}