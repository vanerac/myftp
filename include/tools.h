/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** tools.h file
*/

#ifndef C_TOOLS_H
#define C_TOOLS_H

#include "commands.h"
#include "sessions.h"

command_t parse_command(char *command_raw);

int check_auth(session_t *config);

#endif //C_TOOLS_H
