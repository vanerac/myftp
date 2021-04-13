/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** recv.c file
*/

#include <commands.h>
#include <unistd.h>

int retr(session_t *config, char *argument)
{
    // is there data socket ?
    if (config->data_fd < 0)
        return 1; // todo handle error
    int pid = fork();
    switch(pid) {
    case -1:
        return 1; // todo fail system
    case 0:
        // pipe &return 1;
        break;
    default:
    // waitpid() // todo is this blocking ??
    // close data_fd
        break;
    }
}