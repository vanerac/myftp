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
    (void) argument;
    dprintf(config->ctrl_fd, "257 \"%s\"\r\n", config->working_dir);
    return 0;
}