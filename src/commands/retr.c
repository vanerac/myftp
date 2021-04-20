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

int send_file(session_t *config, char *path)
{
    int fd = open("path", O_WRONLY);
    if (fd == -1) {
        // todo
    }
    return transfer(fd, config->data_fd, 0); // write
}

int retr(session_t *config, char *argument)
{

    // todo path = argument

    // is there data socket ?
    if (config->data_fd < 0)
        return 1; // todo print error


    // todo stat file to check if its real
    char *path;

    int pid = fork();
    switch (pid) {
    case -1:
        return 1; // todo fail system
    case 0:
        if (send_file(config, path)) {
            // todo error
        }
        exit(1);
    default:
        waitpid(pid, NULL, 0); // todo is this blocking ??
        close(config->data_fd);
        config->data_fd = -1;
        break;
    }
    return 0;
}