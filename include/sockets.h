/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** sockets.h file
*/

#ifndef C_SOCKETS_H
#define C_SOCKETS_H

#include "sessions.h"

char *read_socket(int fd);

long int write_socket(int fd, char *buffer);

int open_port(int port);

#endif //C_SOCKETS_H
