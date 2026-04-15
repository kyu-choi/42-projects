# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 20:10:47 by kyu-choi          #+#    #+#              #
#    Updated: 2025/05/11 20:10:49 by kyu-choi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libftprintf.a

HEADER      = ./

SRC_DIR     = src

LIBFT_DIR   = ./libft

SRCS        = ft_printf.c \
              utoa_lowhex.c \
              utoa_uphex.c\
              lltoa_hex.c \
              printchar.c \
              printlowhex.c \
              printuphex.c \
              printint.c \
              printpoint.c \
              printstr.c\
              printunsigned.c\
              utoa.c

OBJS        = $(SRCS:.c=.o)

CC          = cc

CFLAGS      = -Wall -Wextra -Werror -I$(HEADER) -I$(LIBFT_DIR)

AR          = ar rcs

RM          = rm -f

CP	    = cp

all: $(NAME)

$(LIBFT_DIR)/libft.a:
		make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
		$(CP) $(LIBFT_DIR)/libft.a $(NAME)
		$(AR) $(NAME) $(OBJS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)
		make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) $(NAME)
		make fclean -C $(LIBFT_DIR)

re: fclean all


.PHONY: all clean fclean re

