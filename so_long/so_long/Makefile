# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 20:53:33 by kyu-choi          #+#    #+#              #
#    Updated: 2025/08/28 15:43:21 by kyu-choi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC     = gcc
CFLAGS = -Wall -Werror -Wextra -g -I. -I$(MLX_DIR) -I./ft_printf 
LDFLAGS = -no-pie

NAME   = so_long

SRC    = clean_game.c close_click.c get_next_line.c get_next_line_utils.c lender.c load_xpm.c map_check.c map_free_exit.c map_make.c map_valid.c on_configure.c on_key.c on_map.c Queue.c size_handle.c so_long.c third_while_check.c un_map.c

PR_ = ./ft_printf/

SRC_PRINTF = $(PR_)ft_printf.c $(PR_)lltoa_hex.c $(PR_)printchar.c $(PR_)printint.c $(PR_)printlowhex.c $(PR_)printpoint.c $(PR_)printstr.c $(PR_)printunsigned.c $(PR_)printuphex.c $(PR_)utoa.c $(PR_)utoa_lowhex.c $(PR_)utoa_uphex.c
# SRC_LIBFT := $(wildcard ft_printf/libft/*.c)

OBJ    = $(SRC:.c=.o)
OBJ_PRINTF := $(SRC_PRINTF:.c=.o)
# OBJ_LIBFT := $(SRC_LIBFT:.c=.o)

# LIBFT_A = ft_printf/libft/libft.a
PRINTF_A = ft_printf/libftprintf.a

MLX_DIR = minilibx-linux
# 리눅스 mlx 표준 예: -lmlx_Linux + Xext/X11 + m + z
MLXLIB  = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): mlx $(OBJ) $(PRINTF_A) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLXLIB) $(LIBFT_A) $(PRINTF_A)

# mlx 라이브러리 먼저 빌드
mlx:
	$(MAKE) -C $(MLX_DIR)

$(PRINTF_A): $(OBJ_PRINTF)
	$(MAKE) -C ./ft_printf
	
%.o: %.c so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./ft_printf clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(MAKE) -C ./ft_printf fclean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re mlx

