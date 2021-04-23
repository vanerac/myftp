/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include "ftp.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int ac, char **ag)
{
    struct stat s;
    if (ac < 3)
        return 84;
    int port = atoi(ag[1]);
    char *path = ag[2];

    if (stat(path, &s)) {
        perror("stat");
        return 84;
    }

    return ftp(port, path);
}