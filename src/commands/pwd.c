/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** pwd.c file
*/

#include <stdio.h>
#include "commands.h"
#include "sessions.h"

int pwd(session_t *config, char *argument)
{
    if (!config->logged)
        return 0; // todo error message
    (void) argument;
    dprintf(config->ctrl_fd, "257 \"%s\"\r\n", config->working_dir);
    return 0;
}