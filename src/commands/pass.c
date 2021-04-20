/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** pass.c file
*/

#include <commands.h>
#include <string.h>
#include <tools.h>
#include <sockets.h>
#include "sessions.h"

int pass(session_t *config, char *argument)
{
    config->password = strdup(argument);
    if (!check_auth(config) && !config->username)
        write_socket(config->ctrl_fd, "332 Need account for login.");
    else if (!check_auth(config)) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
    } else
        write_socket(config->ctrl_fd, "230 User logged in, proceed.");
    return 0;
}