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
    DEBUG(raw_command);
    command_t command = parse_command(raw_command);
    write(trigger_fd, "Command recv\n", strlen("Command recv\n"));
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

int handle_session(int fd, char *path)
{
    struct sockaddr_in client;
    unsigned long int length = sizeof(client);
    int client_fd = accept(fd, (struct sockaddr *) &client,
        (socklen_t *) &length);
    if (client_fd < 0)
        return -1;
    DEBUG("Got new connection\n")
    createSession(client_fd, &client, path);
    write_socket(client_fd, "220 (OK) Connection Established.");
    return client_fd;
}

int listen_updates(int server_socket, fd_set *rfds, char *path)
{
    FD_SET(server_socket, rfds);

    if (select(FD_SETSIZE, rfds, NULL, NULL, NULL) == -1)
        return 84;
    for (int i = 0; i < FD_SETSIZE; ++i)
        if (FD_ISSET(i, rfds) && i != server_socket)
            handle_commands(i);
        else if (FD_ISSET(i, rfds) && i == server_socket)
            handle_session(server_socket, path); // todo anon path by default
    for (int i = 0; i < FD_SETSIZE; ++i)
        if (sessions[i])
            FD_SET((sessions[i])->ctrl_fd, rfds);
    return 0;
}

int ftp(unsigned short port, char *path)
{

    int fd;

    if ((fd = open_port(port)) < 0)
        return 84;
    initSessions();
    listen(fd, SOMAXCONN);
    fd_set rfds;
    FD_ZERO(&rfds);
    int status = 0;

    while (status == 0)
        status = listen_updates(fd, &rfds, path);

    return 0;
}