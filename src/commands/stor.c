/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** stor.c file
*/

#include <fcntl.h>
#include <stdlib.h>
#include "commands.h"
#include "sockets.h"
#include "tools.h"
#include "sessions.h"

int stor(session_t *config, char *argument)
{
    if (!config->logged) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
        return 0;
    }
    if (config->data_fd < 0) {
        write_socket(config->ctrl_fd, "425 Can't open data connection.");
        return 0;
    }
    if (!argument) {
        write_socket(config->ctrl_fd,
            "501 Syntax error in parameters or arguments.");
        return 0;
    }

    char *buffer = append_path(config->working_dir, argument);

    int fd = open(buffer, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0) {
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
        return 0;
    }
    free(buffer);
    write_socket(config->ctrl_fd,
        "150 File status okay; about to open data connection.");
    transfer(config->data_fd, fd);
    config->data_fd = -1;

    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}