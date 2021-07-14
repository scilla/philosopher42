SRCS			= main.c utils.c life.c ft_atoi.c ft_strdup.c generator.c fork.c print.c ft_calloc.c ft_strlen.c ft_strlcpy.c
SRCS_BONUS		= main_bonus.c utils.c life_bonus.c ft_atoi.c ft_strdup.c fork_bonus.c print_bonus.c generator_bonus.c ft_calloc.c ft_strlen.c ft_strlcpy.c
OBJ				= $(SRCS:.c=.o)
OBJ_BONUS		= $(SRCS_BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g # -lpthread 
NAME			= philosopher

%.o:			%.c
				$(CC) -c -g $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ)

bonus:			fclean $(OBJ_BONUS)
				$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ_BONUS)

clean:
				$(RM) $(OBJ) $(OBJ_BONUS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

g:				fclean $(OBJS)
				gcc -g -o a.out ${SRCS} ${LIBS} 

.PHONY:			all clean fclean re
