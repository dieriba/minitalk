SRC_CLIENT	= client.c utils.c

SRC_SERVER	= server.c utils.c

OBJS_SERVER	= $(SRC_SERVER:.c=.o)

OBJS_CLIENT	= $(SRC_CLIENT:.c=.o)

DEPS_SERVER = $(SRC_SERVER:.c=.d)

DEPS_CLIENT = $(SRC_CLIENT:.c=.d)

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -MMD

SERVER		= server

CLIENT		= client

all:		$(SERVER) $(CLIENT)

.c.o :	
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER):	${OBJS_SERVER}
			make -C ./libft
			cp ./libft/libft.a .
			$(CC) $(CFLAGS) ${OBJS_SERVER} -L. -lft -o $(SERVER)

$(CLIENT):	${OBJS_CLIENT}	
			make -C ./libft
			cp ./libft/libft.a .
			$(CC) $(CFLAGS) $(OBJS_CLIENT) -L. -lft -o $(CLIENT)

clean:
			rm -rf *.o
			rm -rf *.d
			
fclean:		clean
			rm -rf $(SERVER) $(CLIENT) libft.a

re:			fclean all

-include : $(DEPS_CLIENT) $(DEPS_SERVER)

.PHONY:		all clean fclean re