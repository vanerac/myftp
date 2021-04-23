/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** recv.c file
*/

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "commands.h"
#include "sockets.h"
#include "tools.h"
#include "sessions.h"

int retr(session_t *config, char *argument)
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

    int fd = open(buffer, O_RDONLY);
    if (fd < 0) {
        perror("open");
        write_socket(config->ctrl_fd,
            "550 Requested action not taken. File unavailable (e.g., file not found, no access).");
        return 0;
    }

    struct stat s;
    stat(buffer, &s);
    write_socket(config->ctrl_fd,
        "150 File status okay; about to open data connection.");

    free(buffer);
    transfer(fd, config->data_fd);
    config->data_fd = -1;
    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}