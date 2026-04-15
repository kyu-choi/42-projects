# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 14:50:18 by kyu-choi          #+#    #+#              #
#    Updated: 2025/07/24 14:50:19 by kyu-choi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g
CFLAGS = -Wall -Werror -Wextra -I./ -I./ft_printf

NAME = push_swap
BONUS = checker
BONUS_DIR = bonus

PR_ = ./ft_printf/

SRC = find_b_insert_a.c find_win.c ft_atoi.c ft_split.c \
	ft_strncmp.c make_stack.c node_append.c node_count.c \
	print_stack.c push.c reverse_rotate.c rotate.c \
	rotate_push.c small_sort.c sort_index.c swap.c \
	free_stack.c check_stack.c is_sorted.c

PS_MAIN_SRC = push_swap.c
PS_BONUS_MAIN_SRC = $(BONUS_DIR)/checker.c

SRC_PRINTF = $(PR_)ft_printf.c $(PR_)lltoa_hex.c $(PR_)printchar.c $(PR_)printint.c \
	$(PR_)printlowhex.c $(PR_)printpoint.c $(PR_)printstr.c $(PR_)printunsigned.c \
	$(PR_)printuphex.c $(PR_)utoa.c $(PR_)utoa_lowhex.c $(PR_)utoa_uphex.c

BONUS_SRC = $(BONUS_DIR)/checking.c get_next_line.c get_next_line_utils.c \
	$(BONUS_DIR)/b_push.c $(BONUS_DIR)/b_rotate.c \
	$(BONUS_DIR)/b_reverse_rotate.c $(BONUS_DIR)/b_swap.c

OBJ               = $(SRC:.c=.o)
OBJ_PRINTF := $(SRC_PRINTF:.c=.o)
PS_MAIN_OBJ       = $(PS_MAIN_SRC:.c=.o)
PS_BONUS_MAIN_OBJ = $(PS_BONUS_MAIN_SRC:.c=.o)
BONUS_OBJ     = $(BONUS_SRC:.c=.o)

PRINTF_A = ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(PS_MAIN_OBJ) $(PRINTF_A)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(PS_MAIN_OBJ) $(PRINTF_A)

bonus: $(BONUS) 

$(BONUS): $(OBJ) $(PS_BONUS_MAIN_OBJ) $(BONUS_OBJ) $(PRINTF_A)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(PS_BONUS_MAIN_OBJ) $(BONUS_OBJ) $(PRINTF_A)

$(PRINTF_A): $(OBJ_PRINTF)
	$(MAKE) -C ./ft_printf

# 개별 .c -> .o 컴파일 (반드시 -c)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(PS_MAIN_OBJ) $(PS_BONUS_MAIN_OBJ) $(BONUS_OBJ)
	$(MAKE) -C ./ft_printf clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C ./ft_printf fclean

re: fclean all

.PHONY: all clean fclean re bonus

