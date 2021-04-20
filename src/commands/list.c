/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** list.c file
*/

#include <commands.h>
#include <sockets.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "sessions.h"

int list(session_t *config, char *argument)
{
    write_socket(config->ctrl_fd,
        "150 File status okay; about to open data connection.");
    // transmit on data chanel ??

    // todo fork ??
    // todo execve ??
    // todo error management ???
    int pid = fork();
    switch(pid) {
    case -1:
        perror("fork");
        return 1;
    case 0:
        write_socket(config->data_fd, "lol");
        exit(0);
    default:
        waitpid(pid, NULL, 0);
        close(config->data_fd);
        config->data_fd = -1;
    }

    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}