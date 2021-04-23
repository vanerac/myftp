/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** sessions.c file
*/

#include "sessions.h"
#include "ftp.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

session_t *sessions[FD_SETSIZE];

session_t ***getSessions()
{
    static session_t *s_sessions[FD_SETSIZE];
    return (session_t ***) &s_sessions; // todo implement this
}

void initSessions()
{
    memset(sessions, 0, sizeof(session_t *) * FD_SETSIZE);
}

session_t *find_session(int fd)
{
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (sessions[i] && sessions[i]->ctrl_fd == fd)
            return sessions[i];
    }
    return NULL;
}

void deleteSession(int fd)
{
    for (int i = 0; i < FD_SETSIZE; ++i)
        if (sessions[i] && sessions[i]->ctrl_fd == fd) {
            free(sessions[i]->password);
            free(sessions[i]->username);
            free(sessions[i]->working_dir);
            free(sessions[i]);
            sessions[i] = NULL;
        }
}

void createSession(int fd, struct sockaddr_in *in, char *path)
{
    session_t *session = malloc(sizeof(session_t));
    session->ctrl_fd = fd;
    session->data_fd = -1;
    session->username = NULL;
    session->password = NULL;
    session->client_addr = in;
    session->logged = false;
    session->working_dir = strdup(path);

    deleteSession(fd);
    for (int i = 0; i < FD_SETSIZE; ++i)
        if (!sessions[i]) {
            sessions[i] = session;
            break;
        }
    DEBUG("Added Session\n")
}
