/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** my_ftp.h file
*/

#ifndef C_COMMANDS_H
#define C_COMMANDS_H

#include <stddef.h>
#include "ftp.h"

int noop(session_t *config, char *argument);

int user(session_t *config, char *argument);

int pass(session_t *config, char *argument);

int cwd(session_t *config, char *argument);

int quit(session_t *config, char *argument);

int dele(session_t *config, char *argument);

int pwd(session_t *config, char *argument);

int pasv(session_t *config, char *argument);

int port(session_t *config, char *argument);

int help(session_t *config, char *argument);

int retr(session_t *config, char *argument);

int stor(session_t *config, char *argument);

int list(session_t *config, char *argument);

enum commands_e {
    USER,
    PASS,
    CWD,
    QUIT,
    DELE,
    PWD,
    PASV,
    PORT,
    HELP,
    RETR,
    STOR,
    LIST,
    NOOP
};

typedef struct command_s {
    enum commands_e command;
    char *command_name;

    int (*command_functions)(session_t *config, char *argument);

    char *argument;
} command_t;

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

#endif //C_COMMANDS_H
