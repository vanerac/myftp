/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include "ftp.h"
#include <stdlib.h>

int main(int ac, char **ag)
{
    // argv[1] == port
    // argv[2] == path
    if (ac < 3)
        return 84;
    int port = atoi(ag[1]);
    char *path = ag[2];
    return ftp(port, path);
}