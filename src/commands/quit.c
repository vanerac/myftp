/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** quit.c file
*/

#include <commands.h>
#include <sockets.h>
#include <sessions.h>

int quit(session_t *config, char *argument)
{
    write_socket(config->ctrl_fd, "221 Service closing control connection.");
    close(config->ctrl_fd);
    deleteSession(config->ctrl_fd);
    return 0;
}