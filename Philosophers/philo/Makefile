NAME = philo

CC = gcc

CFLAGS = -Werror -Wextra -Wall 

SRC = action.c argv_check.c create_pthread.c five_check.c forks.c free_destroy.c \
	ft_atoi.c ft_strncmp.c init_philo.c init_share.c make_philo.c monitor_routine.c must.c\
	one_philo.c philo.c philo_routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
