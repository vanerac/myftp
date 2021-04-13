/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** my_ftp.c file
*/

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sockets.h"
#include "commands.h"
#include "sessions.h"
#include "tools.h"



int handle_commands(int trigger_fd)
{
    session_t *session = find_session(trigger_fd);
    char *raw_command = read_socket(session->ctrl_fd);
    DEBUG("Got command ")
    DEBUG(raw_command);
    DEBUG("\n");
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
    DEBUG("Got new connection\n")
    createSession(client_fd, &client);
    write_socket(client_fd, "220 (OK) Connection Established.");
    return client_fd;
}

int ftp(unsigned short port, char *path)
{
    fd_set rfds;
    struct timeval tv;
    int retval, status, nfds = 0;
    FD_ZERO(&rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 500;
    int fd = open_port(port);
    if (fd < 0)
        return 84;
    initSessions();

    status = 0;
    while (status == 0) {
        if (!listen(fd, 0)) {
            FD_SET(handle_session(fd), &rfds);
            ++nfds;
        }
        if ((retval = select(nfds, &rfds, NULL, NULL, &tv)))
            status = handle_commands(retval);
    }

    return 0;
}