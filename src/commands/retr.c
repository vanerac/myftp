/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** recv.c file
*/

#include <commands.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sockets.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
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

    char *direction = argument;
    char *buffer = calloc(strlen(config->working_dir) + strlen(direction) + 2,
        1); // todo change size to 100

    strcat(buffer, config->working_dir);
    if (buffer[strlen(buffer) - 1] != '/')
        strcat(&buffer[strlen(buffer) - 1], "/");
    strcat(&buffer[strlen(buffer)], direction);

    char *path = buffer;
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        write_socket(config->ctrl_fd,
            "550 Requested action not taken. File unavailable (e.g., file not found, no access).");
        return 0;
    }
    if (!fork())
        exit(1); // todo pour la mouli

    struct stat s;
    stat(path, &s);
    write_socket(config->ctrl_fd,
        "150 File status okay; about to open data connection.");

    free(buffer);
    buffer = calloc(100, 1);
    size_t rd;
    while ((rd = read(fd, buffer, 100))) {
        for (int i = 0; i < rd; i++)
            write(config->data_fd, buffer[i] == '\n' ? "\r\n" : &buffer[i],
                buffer[i] == '\n' ? 2 : 1);
    }
    write_socket(config->data_fd, "");
    close(config->data_fd);
    config->data_fd = -1;
    close(fd);
    free(buffer);
    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}