/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** ftp.h file
*/

#ifndef C_FTP_H
#define C_FTP_H
typedef struct session_s {
    int ctrl_fd;
    int data_fd;
    char *username;
    char *working_dir;
    struct sockaddr_in client_addr;
} session_t;
#endif //C_FTP_H
