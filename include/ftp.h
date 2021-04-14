/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** ftp.h file
*/

#ifndef C_FTP_H
#define C_FTP_H

#include <stdbool.h>
#include <netinet/in.h>
#include <unistd.h>

#define DEBUG(str) write(1, str, strlen(str));

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
