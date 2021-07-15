SRCS			= main.c utils.c life.c ft_atoi.c ft_strdup.c generator.c fork.c \
					print.c ft_calloc.c ft_strlen.c ft_strlcpy.c
OBJ				= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g
NAME			= philo

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
				$(RM) $(OBJ) $(OBJ_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean $(NAME)

g:				fclean $(OBJS)
				gcc -g -o a.out ${SRCS} ${LIBS} 

.PHONY:			all clean fclean re
