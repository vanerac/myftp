/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** help.c file
*/

#include <commands.h>
#include <sockets.h>
#include "sessions.h"

int help(session_t *config, char *argument)
{

    //    USER <SP> <username> <CRLF>   : Specify user for authentication
    //    PASS <SP> <password> <CRLF>   : Specify password for authentication
    //
    //    CWD  <SP> <pathname> <CRLF>   : Change working directory
    //    CDUP <CRLF>                   : Change working directory to parent directory
    //
    //    QUIT <CRLF>                   : Disconnection
    //
    //    DELE <SP> <pathname> <CRLF>   : Delete file on the server
    //
    //    PWD  <CRLF>                   : Print working directory
    //
    //    PASV <CRLF>                   : Enable "passive" mode for data transfer
    //
    //    PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer
    //
    //
    //    HELP [<SP> <string>] <CRLF>   : List available commands
    //
    //    NOOP <CRLF>                   : Do nothing
    //
    //        (the following are commands using data transfer )
    //
    //    RETR <SP> <pathname> <CRLF>   : Download file from server to client
    //    STOR <SP> <pathname> <CRLF>   : Upload file from client to server
    //    LIST [<SP> <pathname>] <CRLF> : List files in the current working directory

    write_socket(config->ctrl_fd, "214 Help message.");
    return 0;
}