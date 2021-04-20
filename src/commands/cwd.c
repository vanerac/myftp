/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** cwd.c file
*/

#include <commands.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sockets.h>

int cwd(session_t *config, char *argument)
{
    char *direction = argument;

    char *buffer = malloc(strlen(config->working_dir) + strlen(direction) + 1);
    strcat(buffer, config->working_dir);
    strcat(&buffer[strlen(config->working_dir) - 1], "/");
    strcat(&buffer[strlen(config->working_dir)], direction);

    DIR *dir = opendir(buffer);
    if (dir) {
        write_socket(config->ctrl_fd,
            "Requested file action okay, completed.");
        free(config->working_dir);
        config->working_dir = buffer;
    } else {
        // todo invaild dir
    }

    return 0;
}