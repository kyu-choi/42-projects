# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/27 13:11:26 by kyu-choi          #+#    #+#              #
#    Updated: 2025/07/27 13:11:29 by kyu-choi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
CLIENT = client

cc = gcc
CFLAGS = -Wall -Wextra -Werror -I./ft_printf -I./ft_printf/libft
LDFLAGS = -no-pie


SRC_PRINTF := $(wildcard ft_printf/*.c)

SRC_LIBFT := $(wildcard ft_printf/libft/*.c)

OBJ_PRINTF := $(SRC_PRINTF:.c=.o)

OBJ_LIBFT := $(SRC_LIBFT:.c=.o)

SRC_SERVER := server.c

SRC_CLIENT := client.c

OBJ_SERVER := $(SRC_SERVER:.c=.o)

OBJ_CLIENT := $(SRC_CLIENT:.c=.o)

LIBFT_A = ft_printf/libft.a
PRINTF_A = ft_printf/ft_printf.a

all: $(LIBFT_A) $(PRINTF_A) $(NAME) $(CLIENT) 

$(LIBFT_A): $(OBJ_LIBFT)
	ar rcs $@ $^

$(PRINTF_A): $(OBJ_PRINTF)
	ar rcs $@ $^

$(NAME): $(OBJ_SERVER) $(PRINTF_A) $(LIBFT_A)
	$(cc) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ_SERVER) $(PRINTF_A) $(LIBFT_A)
$(CLIENT): $(OBJ_CLIENT) $(PRINTF_A) $(LIBFT_A)
	$(cc) $(CFLAGS) $(LDFLAGS) -o $(CLIENT) $(OBJ_CLIENT) $(PRINTF_A) $(LIBFT_A)
	
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_PRINTF) $(OBJ_LIBFT)
	
fclean: clean
	rm -f $(NAME) $(CLIENT) $(PRINTF_A) $(LIBFT_A)
	
re: fclean all
