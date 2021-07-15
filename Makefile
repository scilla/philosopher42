SRCS			= philo/main.c utils/utils.c philo/life.c utils/ft_atoi.c utils/ft_strdup.c philo/generator.c philo/fork.c \
					philo/print.c utils/ft_calloc.c utils/ft_strlen.c utils/ft_strlcpy.c
SRCS_BONUS		= philo_bonus/main_bonus.c utils/utils.c philo_bonus/life_bonus.c utils/ft_atoi.c \
					utils/ft_strdup.c philo_bonus/fork_bonus.c philo_bonus/print_bonus.c philo_bonus/generator_bonus.c \
					utils/ft_calloc.c utils/ft_strlen.c utils/ft_strlcpy.c
OBJ				= $(SRCS:.c=.o)
OBJ_BONUS		= $(SRCS_BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g
NAME			= philo
NAME_BONUS		= philo_bonus

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

bonus:			fclean $(OBJ_BONUS)
				$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)

clean:
				$(RM) $(OBJ) $(OBJ_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean $(NAME)

g:				fclean $(OBJS)
				gcc -g -o a.out ${SRCS} ${LIBS} 

.PHONY:			all clean fclean re
