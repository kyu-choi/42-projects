# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#              #
#    Updated: 2025/11/23 02:41:00 by hyeonwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./include -I./$(LIBFT_DIR)
LDFLAGS		= -lreadline -L$(LIBFT_DIR) -lft

SRC_DIR		= src
OBJ_DIR		= obj

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	RL_SRC_MAND = $(SRC_DIR)/mandatory/utils/rl_linux.c
	RL_SRC_BONUS = $(SRC_DIR)/bonus/utils/rl_linux_bonus.c
else
	RL_SRC_MAND = $(SRC_DIR)/mandatory/utils/rl_macos.c
	RL_SRC_BONUS = $(SRC_DIR)/bonus/utils/rl_macos_bonus.c
endif

# Mandatory sources
SRCS_MAND	= $(SRC_DIR)/mandatory/main.c \
			  $(SRC_DIR)/mandatory/init/input_processing.c \
			  $(SRC_DIR)/mandatory/init/shell_loop.c \
			  $(SRC_DIR)/mandatory/parser/tokenizer.c \
			  $(SRC_DIR)/mandatory/parser/tokenizer_utils.c \
			  $(SRC_DIR)/mandatory/parser/quotes.c \
			  $(SRC_DIR)/mandatory/parser/expand.c \
			  $(SRC_DIR)/mandatory/parser/expand_heredoc.c \
			  $(SRC_DIR)/mandatory/parser/expand_utils.c \
			  $(SRC_DIR)/mandatory/parser/word_split.c \
			  $(SRC_DIR)/mandatory/parser/token_segments.c \
			  $(SRC_DIR)/mandatory/parser/token_segments_utils.c \
			  $(SRC_DIR)/mandatory/parser/token_segments_helpers.c \
			  $(SRC_DIR)/mandatory/parser/segment_merge.c \
			  $(SRC_DIR)/mandatory/parser/segment_merge_utils.c \
			  $(SRC_DIR)/mandatory/parser/word_split_ext.c \
			  $(SRC_DIR)/mandatory/parser/parser.c \
			  $(SRC_DIR)/mandatory/parser/parser_utils.c \
			  $(SRC_DIR)/mandatory/parser/parser_redir.c \
			  $(SRC_DIR)/mandatory/parser/parser_redir_utils.c \
			  $(SRC_DIR)/mandatory/parser/parser_error.c \
			  $(SRC_DIR)/mandatory/parser/tokenizer_redir.c \
			  $(SRC_DIR)/mandatory/parser/assignment.c \
			  $(SRC_DIR)/mandatory/executor/executor.c \
			  $(SRC_DIR)/mandatory/executor/executor_utils.c \
			  $(SRC_DIR)/mandatory/executor/executor_wait.c \
			  $(SRC_DIR)/mandatory/executor/executor_helpers.c \
			  $(SRC_DIR)/mandatory/executor/path.c \
			  $(SRC_DIR)/mandatory/executor/redirections.c \
			  $(SRC_DIR)/mandatory/executor/heredoc.c \
			  $(SRC_DIR)/mandatory/executor/redir_apply.c \
			  $(SRC_DIR)/mandatory/executor/redir_helpers.c \
			  $(SRC_DIR)/mandatory/executor/pipeline.c \
			  $(SRC_DIR)/mandatory/executor/pipeline_utils.c \
			  $(SRC_DIR)/mandatory/builtins/builtins.c \
			  $(SRC_DIR)/mandatory/builtins/cd.c \
			  $(SRC_DIR)/mandatory/builtins/echo.c \
			  $(SRC_DIR)/mandatory/builtins/env.c \
			  $(SRC_DIR)/mandatory/builtins/exit.c \
			  $(SRC_DIR)/mandatory/builtins/export.c \
			  $(SRC_DIR)/mandatory/builtins/export_display.c \
			  $(SRC_DIR)/mandatory/builtins/export_utils.c \
			  $(SRC_DIR)/mandatory/builtins/history.c \
			  $(SRC_DIR)/mandatory/builtins/pwd.c \
			  $(SRC_DIR)/mandatory/builtins/unset.c \
			  $(SRC_DIR)/mandatory/builtins/source.c \
			  $(SRC_DIR)/mandatory/signals/signals.c \
			  $(SRC_DIR)/mandatory/utils/env.c \
			  $(SRC_DIR)/mandatory/utils/env_init.c \
			  $(SRC_DIR)/mandatory/utils/env_shlvl.c \
			  $(SRC_DIR)/mandatory/utils/env_converter.c \
			  $(SRC_DIR)/mandatory/utils/utils.c \
			  $(RL_SRC_MAND)

# Bonus sources
SRCS_BONUS	= $(SRC_DIR)/bonus/init/main_bonus.c \
			  $(SRC_DIR)/bonus/init/input_processing_bonus.c \
			  $(SRC_DIR)/bonus/init/shell_loop_bonus.c \
			  $(SRC_DIR)/bonus/init/integration_bonus.c \
			  $(SRC_DIR)/bonus/parser/tokenizer_bonus.c \
			  $(SRC_DIR)/bonus/parser/tokenizer_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/tokenizer_redir_bonus.c \
			  $(SRC_DIR)/bonus/parser/tokenizer_fd_bonus.c \
			  $(SRC_DIR)/bonus/parser/quotes_bonus.c \
			  $(SRC_DIR)/bonus/parser/expand_bonus.c \
			  $(SRC_DIR)/bonus/parser/expand_heredoc_bonus.c \
			  $(SRC_DIR)/bonus/parser/expand_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/word_split_bonus.c \
			  $(SRC_DIR)/bonus/parser/token_segments_bonus.c \
			  $(SRC_DIR)/bonus/parser/token_segments_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/token_segments_helpers_bonus.c \
			  $(SRC_DIR)/bonus/parser/segment_merge_bonus.c \
			  $(SRC_DIR)/bonus/parser/segment_merge_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/word_split_ext_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_full_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_full_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_full_helpers_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_redir_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_redir_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_redir_utils2_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_cmd_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_cmd_utils_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_bonus.c \
			  $(SRC_DIR)/bonus/parser/parser_error_bonus.c \
			  $(SRC_DIR)/bonus/parser/assignment_bonus.c \
			  $(SRC_DIR)/bonus/executor/executor_bonus.c \
			  $(SRC_DIR)/bonus/executor/executor_utils_bonus.c \
			  $(SRC_DIR)/bonus/executor/executor_wait_bonus.c \
			  $(SRC_DIR)/bonus/executor/executor_helpers_bonus.c \
			  $(SRC_DIR)/bonus/executor/path_bonus.c \
			  $(SRC_DIR)/bonus/executor/redirections_bonus.c \
			  $(SRC_DIR)/bonus/executor/heredoc_bonus.c \
			  $(SRC_DIR)/bonus/executor/redir_apply_bonus.c \
			  $(SRC_DIR)/bonus/executor/redir_helpers_bonus.c \
			  $(SRC_DIR)/bonus/executor/pipeline_bonus.c \
			  $(SRC_DIR)/bonus/executor/pipeline_utils_bonus.c \
			  $(SRC_DIR)/bonus/executor/background_bonus.c \
			  $(SRC_DIR)/bonus/builtins/builtins_bonus.c \
			  $(SRC_DIR)/bonus/builtins/cd_bonus.c \
			  $(SRC_DIR)/bonus/builtins/echo_bonus.c \
			  $(SRC_DIR)/bonus/builtins/env_bonus.c \
			  $(SRC_DIR)/bonus/builtins/exit_bonus.c \
			  $(SRC_DIR)/bonus/builtins/export_bonus.c \
			  $(SRC_DIR)/bonus/builtins/export_display_bonus.c \
			  $(SRC_DIR)/bonus/builtins/export_utils_bonus.c \
			  $(SRC_DIR)/bonus/builtins/history_bonus.c \
			  $(SRC_DIR)/bonus/builtins/pwd_bonus.c \
			  $(SRC_DIR)/bonus/builtins/unset_bonus.c \
			  $(SRC_DIR)/bonus/builtins/source_bonus.c \
			  $(SRC_DIR)/bonus/signals/signals_bonus.c \
			  $(SRC_DIR)/bonus/utils/env_bonus.c \
			  $(SRC_DIR)/bonus/utils/env_init_bonus.c \
			  $(SRC_DIR)/bonus/utils/env_shlvl_bonus.c \
			  $(SRC_DIR)/bonus/utils/env_converter_bonus.c \
			  $(SRC_DIR)/bonus/utils/utils_bonus.c \
			  $(SRC_DIR)/bonus/operators/operator_bonus.c \
			  $(SRC_DIR)/bonus/operators/subshell_bonus.c \
			  $(SRC_DIR)/bonus/operators/subshell_utils_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_utils_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_redir_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_sort_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_quote_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_path_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_expand_bonus.c \
			  $(SRC_DIR)/bonus/expander/wildcard_array_bonus.c \
			  $(RL_SRC_BONUS)

# Combined sources (mandatory + bonus integrated)
SRCS		= $(SRCS_MAND)
SRCS_B		= $(SRCS_BONUS)

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_B		= $(SRCS_B:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): .mandatory
	@if [ ! -f $(NAME) ]; then \
		$(MAKE) .mandatory; \
	fi

.mandatory: $(LIBFT) $(OBJS)
	@if [ -f .bonus ]; then \
		rm -f .bonus; \
	fi
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@touch .mandatory

bonus: .bonus
	@if [ ! -f $(NAME) ]; then \
		$(MAKE) .bonus; \
	fi

.bonus: $(LIBFT) $(OBJS_B)
	@if [ -f .mandatory ]; then \
		rm -f .mandatory; \
	fi
	$(CC) $(CFLAGS) $(OBJS_B) $(LDFLAGS) -o $(NAME)
	@ln -sf $(NAME) minishell_bonus
	@touch .bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f minishell_bonus
	rm -f .mandatory .bonus

re: fclean all

.PHONY: all clean fclean re
