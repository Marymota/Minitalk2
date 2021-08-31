SRCS_1	= src/client.c

SRCS_2 	= src/server.c

INCLUDE = inc/minitalk.h

OBJ		= $(SRCS_1:.c=.o)

OBJ2    = $(SRCS_2:.c=.o)

FLAGS	= -Wall -Wextra -Werror

all : $(OBJ) $(OBJ2)
		gcc $(FLAGS) -I $(INCLUDE) $(SRCS_1) -o client
		gcc $(FLAGS) -I $(INCLUDE) $(SRCS_2) -o server


clean:
	rm -rf $(OBJ) $(OBJ2)

fclean: clean
	rm -f client server

re: fclean all