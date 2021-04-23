/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** tools.c file
*/

#include <commands.h>
#include <string.h>
#include <stdlib.h>
#include <sockets.h>
#include <stdio.h>
#include "sessions.h"

const command_t command_list[] = {{USER, "USER", &user, NULL},
    {PASS, "PASS", &pass, NULL}, {CDUP, "CDUP", &cdup, NULL},
    {CWD, "CWD", &cwd, NULL}, {QUIT, "QUIT", &quit, NULL},
    {DELE, "DELE", &dele, NULL}, {PWD, "PWD", &pwd, NULL},
    {PASV, "PASV", &pasv, NULL}, {PORT, "PORT", &port, NULL},
    {HELP, "HELP", &help, NULL}, {RETR, "RETR", &retr, NULL},
    {STOR, "STOR", &stor, NULL}, {LIST, "LIST", &list, NULL},
    {SYST, "SYST", &syst, NULL}, {NOOP, "NOOP", &noop, NULL},
    {INVALID, "", &invalid, NULL}};

char *append_path(char *path1, char *path2)
{
    char *buffer = calloc(strlen(path1) + strlen(path2) + 2, 1);
    strcat(buffer, path1);
    if (buffer[strlen(buffer) - 1] != '/')
        strcat(&buffer[strlen(buffer) - 1], "/");
    strcat(&buffer[strlen(buffer)], path2);
    return buffer;
}

void transfer(int fd_from, int fd_to)
{
    size_t rd;
    char *buffer = malloc(100);
    while ((rd = read(fd_from, buffer, 100)))
        write(fd_to, buffer, rd);
    close(fd_from);
    close(fd_to);
}

char *trim_str(char *str)
{
    if (!str)
        return NULL;
    for (; *str == ' ' || *str == '\n' || *str == '\r'; ++str);
    if (!strlen(str))
        return NULL;
    int i = strlen(str) - 1;
    for (; str[i] == ' ' || str[i] == '\n' || str[i] == '\r'; i--)
        str[i] = '\0';
    return str;
}

int check_auth(session_t *config)
{
    if (!strcmp(config->username, "Anonymous"))
        return (config->logged = 1);
    if (!config->username || !config->password)
        return 0;
    return 0;
}

command_t parse_command(char *command_raw)
{
    char *command_name = command_raw;
    char *argument = NULL;
    command_t ret = command_list[INVALID];
    for (int i = 0; command_raw[i] && !argument; ++i) {
        if (command_raw[i] != ' ')
            continue;
        command_name = strndup(command_raw, i);
        argument = strdup(&command_raw[i + 1]); // todo might overflow
    }
    for (int i = 0; i < INVALID; ++i) {
        if (strncmp(command_name, command_list[i].command_name,
            strlen(command_list[i].command_name)) != 0)
            continue;
        ret = command_list[i], ret.argument = trim_str(argument);
        break;
    }
    if (command_name != command_raw)
        free(command_name);
    free(command_raw);
    return ret;
}