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
#include <sys/wait.h>
#include <sockets.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include "sessions.h"

int retr(session_t *config, char *argument)
{
    if (!config->logged)
        return 0; // todo error message
    if (config->data_fd < 0)
        return 1; // todo print error

    if (!argument)
        return 1; // todo handle this

    char *direction = argument;
    char *buffer = calloc(strlen(config->working_dir) + strlen(direction) + 2,
        1);

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

    struct stat s;
    stat(path, &s);
    write_socket(config->ctrl_fd,
        "150 File status okay; about to open data connection.");
    int pid = fork();
    switch (pid) {
    case -1:
        return 1;
    case 0:

        exit(1);
    default:
        printf("sent: %lu bytes\n",
            sendfile(config->data_fd, fd, 0, s.st_size));

        close(config->data_fd);
        close(fd);
        config->data_fd = -1;
        break;
    }
    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}