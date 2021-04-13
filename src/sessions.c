/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** sessions.c file
*/

#include "ftp.h"
#include <netdb.h>
#include <stddef.h>
#include <string.h>

session_t *sessions[SOMAXCONN];

void initSessions()
{
    memset(sessions, 0, sizeof(session_t *) * SOMAXCONN);
}

session_t *find_session(int fd)
{
    for (int i = 0; i < SOMAXCONN; ++i) {
        if (sessions[i] && sessions[i]->ctrl_fd == fd)
            return sessions[i];
    }
    return NULL;
}

void createSession(int fd, struct sockaddr_in *in)
{
    session_t session;
    session.ctrl_fd = fd;
    session.data_fd = -1;
    session.username = NULL;
    session.client_addr = in;
    session.logged = false;
    session.working_dir = NULL; // todo might have to init somewhere else

    for (int i = 0; i < SOMAXCONN; ++i)
        if (!sessions[i])
            sessions[i] = &session; // todo might have to malloc

}

void deleteSession(int fd)
{
    for (int i = 0; i < SOMAXCONN; ++i)
        if (sessions[i] && sessions[i]->ctrl_fd == fd)
            sessions[i] = NULL; // todo might have to free
}