/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** user.c file
*/

#include <tools.h>
#include <sockets.h>
#include <string.h>
#include "commands.h"
#include "sessions.h"

int user(session_t *config, char *argument)
{
    config->username = strdup(argument);
    if (!config->password)
        write_socket(config->ctrl_fd, "331 User name okay, need password.");
    else if (!check_auth(config)) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
    } else
        write_socket(config->ctrl_fd, "230 User logged in, proceed.");
    return 0;
}