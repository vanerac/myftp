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

void createSession(int fd, struct sockaddr_in *in);

void deleteSession(int fd);

#endif //C_SESSIONS_H
