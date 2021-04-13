/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** tools.c file
*/

#include <commands.h>
#include <string.h>
#include <stdlib.h>

command_t command_list[] = {
    {USER, "USER", &user, NULL},
    {PASS, "PASS", &pass, NULL},
    {CWD, "CWD", &cwd, NULL},
    {QUIT, "QUIT", &quit, NULL},
    {DELE, "DELE", &dele, NULL},
    {PWD, "PWD", &pwd, NULL},
    {PASV, "PASV", &pasv, NULL},
    {PORT, "PORT", &port, NULL},
    {HELP, "HELP", &help, NULL},
    {RETR, "RETR", &retr, NULL},
    {STOR, "STOR", &stor, NULL},
    {LIST, "LIST", &list, NULL},
    {NOOP, "NOOP", &noop, NULL}
};

command_t parse_command(char *command_raw)
{
    char *command_name = command_raw;
    char *argument = NULL;
    command_t ret = command_list[NOOP];

    for (int i = 0; command_raw[i]; ++i) {
        if (command_raw[i] != ' ')
            continue;
        command_name = strndup(command_raw, i > 0 ? i - 1 : i);
        argument = strdup(&command_raw[i + 1]); // todo might overflow
    }

    for (int i = 0; i < NOOP; ++i) {
        if (strcmp(command_name, command_list[i].command_name) != 0)
            continue;
        ret = command_list[i];
        ret.argument = argument;
        break;
    }
    free(command_name);
    free(command_raw);
    return ret;
}