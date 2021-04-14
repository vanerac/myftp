/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** my_ftp.c file
*/

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "sockets.h"
#include "commands.h"
#include "sessions.h"
#include "tools.h"

int handle_commands(int trigger_fd)
{
    session_t *session = find_session(trigger_fd);
    char *raw_command = read_socket(session->ctrl_fd);
    command_t command = parse_command(raw_command);

    int status = (*command.command_functions)(session, command.argument);
    free(command.argument);
    if (status) {
        DEBUG("Command exit\n")
        deleteSession(session->ctrl_fd);
        close(session->ctrl_fd);
        return status;
    }
    return 0;
}

int handle_session(int fd)
{
    struct sockaddr_in client;
    unsigned long int length = sizeof(client);
    int client_fd = accept(fd, (struct sockaddr *) &client,
        (socklen_t *) &length);
    if (client_fd < 0)
        return -1;
    DEBUG("Got new connection\n")
    createSession(client_fd, &client);
    write_socket(client_fd, "220 (OK) Connection Established.");
    return client_fd;
}

int ftp(unsigned short port, char *path)
{
    fd_set rfds;
    struct timeval tv;
    int status = 0, new_con, fd;
    FD_ZERO(&rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 500;
    if ((fd = open_port(port)) < 0)
        return 84;
    initSessions();
    fcntl(fd, F_SETFL, O_NONBLOCK);
    listen(fd, SOMAXCONN);

    while (status == 0) {
        select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
        for (int i = 0; i < FD_SETSIZE; ++i)
            if (FD_ISSET(i, &rfds))
                status = handle_commands(i);
        if ((new_con = handle_session(fd)) > 0)
            FD_SET(new_con, &rfds);
    }
    return 0;
}