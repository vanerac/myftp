/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** syst.c file
*/


#include <sockets.h>
#include "commands.h"
#include "sessions.h"

int syst(session_t *config, char *argument)
{
    (void) argument;
    write_socket(config->ctrl_fd, "215 UNIX Type: L8");
    return 0;
}