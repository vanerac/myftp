/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** port.c file
*/

#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include "sockets.h"
#include "sessions.h"
#include "commands.h"

static int error_check(session_t *config, char *argument)
{
    if (!config->logged) {
        write_socket(config->ctrl_fd, "530 Not logged in.");
        return 1;
    }
    if (config->data_fd != -1) {
        write_socket(config->ctrl_fd, "125 Data connection already open");
        return 1;
    }
    if (!argument) {
        write_socket(config->ctrl_fd,
            "501 Syntax error in parameters or arguments.");
        return 1;
    }
    return 0;
}

static int try_connection(char *ip, int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if (connect(fd, (const struct sockaddr *) &serverAddr,
        sizeof(serverAddr))) {
        return -1;
    }
    free(ip);
    return fd;
}

int port(session_t *config, char *argument)
{
    if (error_check(config, argument))
        return 0;

    int i = 0;
    for (int count = 0; argument[i] != '\0'; ++i)
        if (argument[i] == ',' && count < 3)
            argument[i] = '.', count++;
        else if (argument[i] == ',')
            break;
    char *ptr = index(&argument[i], ',');
    int p1 = atoi(++ptr);
    ptr = index(ptr, ',');
    int p2 = atoi(++ptr);

    if ((config->data_fd = try_connection(strndup(argument, i),
        p1 * 256 + p2)) < 0)
        write_socket(config->ctrl_fd, "425 Can't open data connection.");

    write_socket(config->ctrl_fd, "200 Command okay.");
    return 0;
}