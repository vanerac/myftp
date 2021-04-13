/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** ftp.h file
*/

#ifndef C_FTP_H
#define C_FTP_H

#include <netdb.h>
#include <stdbool.h>

typedef struct session_s {
    int ctrl_fd;
    int data_fd;
    char *username;
    char *working_dir;
    bool logged;
    struct sockaddr_in *client_addr;
} session_t;

//session_t *sessions[SOMAXCONN];

int ftp(unsigned short port, char *path);

#endif //C_FTP_H
