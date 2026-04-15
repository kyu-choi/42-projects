# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 19:04:54 by hyeonwki          #+#    #+#              #
#    Updated: 2025/07/04 02:32:12 by hyeonwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library archive
NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# List of all source files (.c)
# Add your get_next_line and ft_printf files here
SRCS =  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
        ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
        ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
        ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
        ft_atoi.c ft_calloc.c ft_strdup.c \
        ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
        ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
        ft_putendl_fd.c ft_putnbr_fd.c \
        get_next_line.c get_next_line_utils.c \
        ft_printf_main.c ft_printf_parse_flags.c \
		ft_printf_dispatch.c ft_printf_handlers_alpha.c \
		ft_printf_alpha_utils.c ft_printf_os_specific.c \
		ft_printf_handlers_numeric.c ft_printf_handle_padding.c \
		ft_printf_utils.c ft_atoi_base.c ft_free_split.c \
		ft_realloc.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstsize.c ft_lstlast.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Generate object file names from source files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(NAME)

# Rule to create the library archive from object files
# The 'ar' command is used to create static libraries (archives).
# 'rcs' flags mean: r - replace/add file, c - create archive, s - create index.
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean object files
clean:
	rm -f $(OBJS)

# Rule to clean everything
fclean: clean
	rm -f $(NAME)

# Rule to re-compile
re: fclean all

.PHONY: all clean fclean re