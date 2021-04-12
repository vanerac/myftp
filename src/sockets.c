/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** sockets.c file
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2024

int transfer(int fd_from, int fd_to)
{
    // todo pipe fd ...
    return 0;
}

char *read_socket(int fd)
{
    char *buffer = calloc(sizeof(char), BUFFER_SIZE);
    read(fd, buffer, BUFFER_SIZE);
    return buffer;
}

long int write_socket(int fd, char *buffer)
{
    return write(fd, buffer, strlen(buffer));
}

int open_port(int port)
{
    int ret_fd = socket(AF_INET, SOCK_STREAM, 0);
    int s = 0;
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;

    serverAddr.sin_addr.s_addr = INADDR_ANY;

    serverAddr.sin_port = htons(port);
    s = bind(ret_fd, (struct sockaddr *) &serverAddr,
        sizeof(serverAddr));
    if (s < 0) {
        perror("bind");
        return -1;
    }
    return ret_fd;
}