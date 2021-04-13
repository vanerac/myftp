/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** user.c file
*/

#include "commands.h"

int user(session_t *config, char *argument)
{
    config->username = argument;
}