/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** invalid.c file
*/

#include "commands.h"
#include "sockets.h"
#include "sessions.h"

int invalid(session_t *config, char *argument)
{
    (void) argument;
    write_socket(config->ctrl_fd, "500 Syntax error, command unrecognized.");
    return 0;
}