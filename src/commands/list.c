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
#include <dirent.h>
#include "commands.h"
#include "sockets.h"
#include "sessions.h"

int list(session_t *config, char *argument)
{
    if (!config->logged) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
        return 0;
    }
    struct stat s;
    char *direction = argument;
    char *buffer;

    if (config->data_fd < 0) {
        write_socket(config->ctrl_fd, "425 Can't open data connection.");
        return 0;
    }

    if (direction) {
        buffer = calloc(strlen(config->working_dir) + strlen(direction) + 2,
            1);
        strcat(buffer, config->working_dir);
        if (buffer[strlen(buffer) - 1] != '/')
            strcat(&buffer[strlen(buffer) - 1], "/");
        strcat(&buffer[strlen(buffer)], direction);
    } else
        buffer = strdup(config->working_dir);

//    if (!fork())
//        exit(1); // todo pour la mouli

    DIR *dir = opendir(buffer);
    if (dir) {
        write_socket(config->ctrl_fd,
            "150 File status okay; about to open data connection.");
        for (struct dirent *f = readdir(dir); f; f = readdir(dir), write(
            config->data_fd, " ", 1)) {
            write(config->data_fd, f->d_name, strlen(f->d_name));
        }
        close(config->data_fd);
        config->data_fd = -1;
    } else
        write_socket(config->ctrl_fd, "550 Requested action not taken.");
    closedir(dir);

    free(buffer);
    write_socket(config->ctrl_fd, "226 Closing data connection.");
    return 0;
}