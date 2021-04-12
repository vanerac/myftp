/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** my_ftp.c file
*/

#include "sockets.h"
#include <sys/socket.h>
#include <netdb.h>
#include <commands.h>
#include <tools.h>
#include <unistd.h>
#include <stdlib.h>

int handle_session(int fd)
{
    // todo handle sessions
    struct sockaddr_in client;
    unsigned long int length = sizeof(client);
    int client_fd = accept(fd, (struct sockaddr *) &client,
        (socklen_t *) &length);

    char *raw_command;
    while ((raw_command = read_socket(client_fd))) {
        command_t command = parse_command(raw_command);
        int status = (*command.command_functions)(command.argument);
        free(command.argument);
        if (status) {
            close(client_fd);
            return status;
        }
    }
    return 0;
}

int ftp(unsigned short port, char *path)
{

    int fd = open_port(port);
    if (fd < 0)
        return 84;

    while (listen(fd, SOMAXCONN)) {
        // todo use select instead
//        switch (fork()) {
//        case 0:
//            return handle_session(fd);
//        case -1:
//            return 84;
//        default:
//            break;
//        }
    }

    return 0;
}