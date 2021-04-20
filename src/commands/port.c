/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** port.c file
*/

#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <libnet.h>
#include "sessions.h"
#include "commands.h"

int port(session_t *config, char *argument)
{
    // 200 Command okay.

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int i = 0;

    for (int count = 0; argument[i] != '\0'; ++i) {
        if (argument[i] == ',' && count < 4)
            argument[i] = '.', count++;
        else if (argument[i] == ',')
            break;
    }

    char *ptr = index(&argument[i], ',');
    int p1 = atoi(ptr);
    ptr = index(ptr, ',');
    int p2 = atoi(ptr);

    int data_port = p1 * 256 + p2;

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(strndup(argument, i));
    serverAddr.sin_port = htons(data_port);

    if (connect(fd, (const struct sockaddr *) &serverAddr,
        sizeof(serverAddr))) {
        // not connected
    }

    config->data_fd = fd;

    return 0;
}