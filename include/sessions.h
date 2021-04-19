/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** sessions.h file
*/

#ifndef C_SESSIONS_H
#define C_SESSIONS_H

void initSessions();

session_t *find_session(int fd);

void createSession(int fd, struct sockaddr_in *in, char *path);

void deleteSession(int fd);

session_t ***getSessions();

#define SESSIONS(void) *(getSessions())

#endif //C_SESSIONS_H
