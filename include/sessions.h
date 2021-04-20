/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** sessions.h file
*/

#ifndef C_SESSIONS_H
#define C_SESSIONS_H

#include <stdbool.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct session_s {
    int ctrl_fd;
    int data_fd;
    char *username;
    char *password;
    char *working_dir;
    char *home_dir;
    bool logged;
    struct sockaddr_in *client_addr;
} session_t;

void initSessions();

session_t *find_session(int fd);

void createSession(int fd, struct sockaddr_in *in, char *path);

void deleteSession(int fd);

session_t ***getSessions();

#define SESSIONS(void) *(getSessions())


#endif //C_SESSIONS_H
