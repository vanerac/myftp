##
## EPITECH PROJECT, 2019
## base_repo
## File description:
## Makefile file
##

SRC		=		src/ftp.c\
				src/sessions.c\
				src/sockets.c\
				src/tools.c\
				src/commands/cwd.c\
				src/commands/help.c\
				src/commands/noop.c\
				src/commands/pasv.c\
				src/commands/pwd.c\
				src/commands/retr.c\
				src/commands/user.c\
				src/commands/dele.c\
				src/commands/list.c\
				src/commands/pass.c\
				src/commands/port.c\
				src/commands/quit.c\
				src/commands/cdup.c\
				src/commands/syst.c\
				src/commands/invalid.c\
				src/commands/stor.c


OBJ		=		$(SRC:%.c=%.o)

MAIN	=		src/main.c
OMAIN	=		$(MAIN:.c=.o)

CFLAGS	=		-Iinclude/ -Wall -Wextra

NAME	=		myftp


all:	$(NAME)

$(NAME): $(OBJ) $(OMAIN)
	gcc -o $(NAME) $(OBJ) $(OMAIN) $(CFLAGS)

clean:
	rm -rf $(OBJ)
	rm -rf $(OTRC)
	rm -rf $(OMAIN)

fclean:	clean
	rm -rf $(NAME)
	rm -rf unit_test

gclean:	fclean clean
	find . -name "*.gc*" -delete

re: gclean all

tests_run:	$(OTRC) $(OBJ)
	gcc -o unit_test $(TRC) $(SRC) $(CFLAGS) -lcriterion --coverage
	#./$(NAME) 5800 `pwd` &
	./unit_test

.PHONY:			gclean clean fclean re tests_run all
