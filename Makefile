SRCS			= main.c utils.c life.c ft_atoi.c generator.c fork.c
SRCS_BONUS		= main_bonus.c utils.c life.c ft_atoi.c
OBJ				= $(SRCS:.c=.o)
OBJ_BONUS		= $(SRCS_BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -lpthread 
NAME			= philosopher

%.o:			%.c
				$(CC) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ)

bonus:			$(OBJ_BONUS)
				$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ_BONUS)

clean:
				$(RM) $(OBJ) $(OBJ_BONUS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

g:				fclean $(OBJS)
				gcc -g -o a.out ${SRCS} ${LIBS} 

.PHONY:			all clean fclean re
