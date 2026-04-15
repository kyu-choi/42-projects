NAME = philo_bonus

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = action.c all.c argv_check.c child_main.c close_unlink_free.c five_check.c ft_atoi.c\
	make_child.c monitor_main.c one_philo.c philo_bonus.c sema_init.c start_child.c must.c\
	full_monitor_start.c full_main.c init_check.c

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
