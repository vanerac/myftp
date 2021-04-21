/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** list.c file
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "commands.h"
#include "sockets.h"
#include "sessions.h"

int list(session_t *config, char *argument)
{
    struct stat s;
    char *direction = argument;
    char *buffer;

    if (direction) {
        buffer = calloc(strlen(config->working_dir) + strlen(direction) + 2,
            1);
        strcat(buffer, config->working_dir);
        if (buffer[strlen(buffer) - 1] != '/')
            strcat(&buffer[strlen(buffer) - 1], "/");
        strcat(&buffer[strlen(buffer)], direction);
    } else
        buffer = strdup(config->working_dir);

    if (stat(buffer, &s)) {
        write_socket(config->ctrl_fd,
            "550 Requested action not taken. File unavailable (e.g., file not found, no access).");
        return 0;
    }

    write_socket(config->ctrl_fd,
        "150 File status okay; about to open data connection.");

    char *args[3] = {"ls", buffer, NULL};

    int pid = fork();
    switch (pid) {
    case -1:
        perror("fork");
        return 1;
    case 0:
        dup2(config->data_fd, 1);
        dup2(config->data_fd, 2);
        execvp("ls", args);
        write_socket(config->data_fd, "");
        exit(0);
    default:
        waitpid(pid, NULL, 0);
        close(config->data_fd);
        config->data_fd = -1;
    }

    free(buffer);
    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}