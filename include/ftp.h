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

//session_t *sessions[SOMAXCONN];

int ftp(unsigned short port, char *path);

#endif //C_FTP_H
