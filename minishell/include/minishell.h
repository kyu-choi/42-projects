/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

void		ft_replace_line(const char *text, int clear);

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_END
}	t_token_type;

typedef struct s_merge_ctx
{
	char	***results;
	int		*count;
	char	**current;
}	t_merge_ctx;

typedef struct s_segment
{
	char				*value;
	int					quoted;
	struct s_segment	*next;
}	t_segment;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				has_quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	int				expand_heredoc;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	t_token_type	operator;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		last_exit_status;
	int		stdin_backup;
	int		stdout_backup;
	int		parse_error_type;
	int		is_interactive;
}	t_shell;

extern int	g_signal;

/* ========================================================================== */
/*                            PARSER - TOKENIZER                             */
/* ========================================================================== */

/**
 * @brief Tokenizes input line into token list
 * @param line Input string to tokenize
 * @return Pointer to first token, NULL on error
 */
t_token		*tokenize(char *line);

/**
 * @brief Creates a new token with given type and value
 * @param type Token type (WORD, PIPE, REDIR, etc.)
 * @param value Token string value
 * @return Newly allocated token, NULL on error
 */
t_token		*create_token(t_token_type type, char *value);

/**
 * @brief Frees entire token linked list
 * @param tokens Head of token list to free
 */
void		free_tokens(t_token *tokens);

/**
 * @brief Skips quoted section in tokenizer
 * @param str Input string
 * @param i Current index in string
 * @return Index after closing quote
 */
int			skip_quotes_in_tokenizer(char *str, int i);

/**
 * @brief Calculates word length for tokenizer
 * @param str Input string starting at word
 * @return Length of word token
 */
int			get_word_len_for_tokenizer(char *str);

/**
 * @brief Extracts word from string for tokenizer
 * @param str Input string starting at word
 * @return Newly allocated word string
 */
char		*extract_word_for_tokenizer(char *str);

/**
 * @brief Adds token to end of token list
 * @param head Pointer to head of token list
 * @param new_token Token to add
 */
void		add_token_to_list_util(t_token **head, t_token *new_token);

/**
 * @brief Prints syntax error with specific token
 * @param token Token string that caused the error (e.g., "|", "&&")
 * @details Outputs: "minishell: syntax error near unexpected token `token'"
 */
void		print_syntax_error(const char *token);

/* ========================================================================== */
/*                            PARSER - QUOTES                                */
/* ========================================================================== */

/**
 * @brief Checks if character is a quote (' or ")
 * @param c Character to check
 * @return 1 if quote, 0 otherwise
 */
int			is_quote(char c);

/**
 * @brief Finds index of closing quote
 * @param str String to search in
 * @param quote Quote character to find
 * @return Index of closing quote, -1 if not found
 */
int			find_closing_quote(char *str, char quote);

/**
 * @brief Removes outer quotes from string
 * @param str String with quotes
 * @return Newly allocated string without quotes
 */
char		*remove_quotes(char *str);
int			get_unclosed_quote(char *str);

/* ========================================================================== */
/*                            PARSER - EXPANSION                             */
/* ========================================================================== */

/**
 * @brief Expands environment variables in string
 * @param str Input string with $VAR references
 * @param shell Shell state with environment
 * @return Newly allocated expanded string
 */
char		*expand_variables(char *str, t_shell *shell);
char		*expand_heredoc_variables(char *str, t_shell *shell);

/**
 * @brief Expands single variable at position
 * @param str Input string
 * @param i Pointer to current index (updated)
 * @param shell Shell state with environment
 * @return Expanded variable value
 */
char		*expand_variable_in_str(char *str, int *i, t_shell *shell);

/**
 * @brief Appends single character to string
 * @param result String to append to
 * @param c Character to append
 * @return Newly allocated string with character appended
 */
char		*append_char_to_str(char *result, char c);

/**
 * @brief Handles single quote section during expansion
 * @param str Input string
 * @param i Pointer to current index (updated)
 * @param result Current result string
 * @return Updated result with literal content
 */
char		*handle_single_quote_expand(char *str, int *i, char *result);

/**
 * @brief Handles variable expansion during parsing
 * @param str Input string
 * @param i Pointer to current index (updated)
 * @param res Current result string
 * @param shell Shell state with environment
 * @return Updated result with expanded variable
 */
char		*handle_variable_expand(char *str, int *i, char *res,
				t_shell *shell);

/**
 * @brief Handles backslash escape sequences
 * @param str Input string
 * @param i Pointer to current index
 * @param res Current result string
 * @param in_dq In double quote flag
 * @return Updated result string
 */
char		*handle_backslash(char *str, int *i, char *res, int in_dq);

/**
 * @brief Expands tilde to HOME directory
 * @param i Pointer to current index (at ~)
 * @param res Current result string
 * @param shell Shell state with environment
 * @param str Input string
 * @return Updated result with expanded tilde or literal ~
 */
char		*handle_tilde_expand(int *i, char *res, t_shell *shell, char *str);

/* ========================================================================== */
/*                            PARSER - MAIN PARSER                           */
/* ========================================================================== */

/**
 * @brief Parses token list into command pipeline
 * @param tokens Token list from tokenizer
 * @param shell Shell state for variable expansion
 * @return Command pipeline, NULL on error
 */
t_cmd		*parse(t_token *tokens, t_shell *shell);

/**
 * @brief Frees entire command pipeline
 * @param cmds Head of command list
 */
void		free_cmds(t_cmd *cmds);

/**
 * @brief Counts number of tokens in list
 * @param tokens Token list to count
 * @return Number of tokens
 */
int			count_tokens_util(t_token *tokens);

/**
 * @brief Creates empty command structure
 * @return Newly allocated command
 */
t_cmd		*create_cmd_util(void);

/**
 * @brief Processes token value (quotes + expansion)
 * @param value Token value to process
 * @param shell Shell state for expansion
 * @return Processed string
 */
char		*process_token_value_util(char *value, t_shell *shell);
char		**split_words(char *str);

/**
 * @brief Checks if string is a variable assignment (VAR=value)
 * @param str String to check
 * @return 1 if assignment pattern, 0 otherwise
 */
int			is_assignment(char *str);

/**
 * @brief Handles variable assignment (VAR=value)
 * @param str Assignment string
 * @param shell Shell state
 * @return 0 on success, 1 on error
 */
int			handle_assignment(char *str, t_shell *shell);

/**
 * @brief Splits token into quoted/unquoted segments
 * @param value Token value
 * @return Segment list
 */
t_segment	*split_into_segments(char *value);

/**
 * @brief Creates new segment
 * @param value Segment value
 * @param quoted Quote type (0=none, 1=single, 2=double)
 * @return New segment
 */
t_segment	*create_segment(char *value, int quoted);

/**
 * @brief Frees segment list
 * @param segments Segment list
 */
void		free_segments(t_segment *segments);

/**
 * @brief Processes segments into fields with proper merging
 * @param segments Segment list
 * @param shell Shell state
 * @param result_count Pointer to store result count
 * @return Array of field strings
 */
char		**process_segments_to_fields(t_segment *segments,
				t_shell *shell, int *result_count);

/**
 * @brief Checks if string has leading whitespace
 * @param str String to check
 * @return 1 if has leading whitespace
 */
int			has_leading_ifs(char *str);

/**
 * @brief Checks if string has trailing whitespace
 * @param str String to check
 * @return 1 if has trailing whitespace
 */
int			has_trailing_ifs(char *str);

/**
 * @brief Fills command args array from tokens
 * @param cmd Command to fill
 * @param tokens Token list to process
 * @param shell Shell state for expansion
 */
void		fill_cmd_args_util(t_cmd *cmd, t_token *tokens, t_shell *shell);

/**
 * @brief Checks if token is a redirection
 * @param type Token type to check
 * @return 1 if redirection, 0 otherwise
 */
int			is_redir_token(t_token_type type);

/**
 * @brief Handles redirection token during parsing
 * @param tok Current token
 * @param cmd Command to add redirection to
 * @param shell Shell state for expansion
 * @return Next token after redirection
 */
t_token		*handle_redir_in_parse(t_token *tok, t_cmd *cmd, t_shell *shell);

/**
 * @brief Counts word tokens (non-redir) in list
 * @param tokens Token list to count
 * @return Number of word tokens
 */
int			count_word_tokens(t_token *tokens);

/**
 * @brief Fills command with redirections from tokens
 * @param cmd Command to fill
 * @param tok Token list to process
 * @param shell Shell state for expansion
 * @return Next token after command
 */
t_token		*fill_cmd_with_redirs(t_cmd *cmd, t_token *tok, t_shell *shell);

/**
 * @brief Parses one command from token stream
 * @param tokens Pointer to token stream
 * @param shell Shell state
 * @return Newly allocated command structure
 */
t_cmd		*parse_one_cmd(t_token **tokens, t_shell *shell);

/**
 * @brief Parses next command in pipeline (helper)
 * @param tokens Pointer to current token
 * @param current Current command
 * @param shell Shell state
 * @return New command or NULL on error
 */
t_cmd		*parse_next_cmd_util(t_token **tokens, t_cmd *current,
				t_shell *shell);

/**
 * @brief Checks if token list ends with a trailing operator
 * @param tokens Token list to check
 * @return 1 if ends with pipe/and/or, 0 otherwise
 */
int			has_trailing_operator(t_token *tokens);

/**
 * @brief Checks for redirection token (<, >, <<, >>)
 * @param str Input string
 * @param i Pointer to current index (updated)
 * @param head Pointer to token list head
 * @return 1 if redirection found, 0 otherwise
 */
int			check_redir_token(char *str, int *i, t_token **head);

/**
 * @brief Checks for additional redirection types
 * @param str Input string
 * @param i Pointer to current index (updated)
 * @param head Pointer to token list head
 * @return 1 if redirection found, 0 otherwise
 */
int			check_redir_token2(char *str, int *i, t_token **head);

/**
 * @brief Checks for pipe token (|)
 * @param str Input string
 * @param i Pointer to current index (updated)
 * @param head Pointer to token list head
 * @return 1 if pipe found, 0 otherwise
 */
int			check_pipe_token(char *str, int *i, t_token **head);

/* ========================================================================== */
/*                            EXECUTOR - MAIN                                */
/* ========================================================================== */

/**
 * @brief Executes command pipeline
 * @param shell Shell state with environment
 * @param cmds Command pipeline to execute
 * @return Exit status of last command
 */
int			execute(t_shell *shell, t_cmd *cmds);

/* ========================================================================== */
/*                            EXECUTOR - REDIRECTIONS                        */
/* ========================================================================== */

/**
 * @brief Creates new redirection node
 * @param type Redirection type (<, >, <<, >>)
 * @param file Target filename
 * @return Newly allocated redirection
 */
t_redir		*create_redir(t_token_type type, char *file, int expand);

/**
 * @brief Adds redirection to list
 * @param head Pointer to redirection list head
 * @param new_redir Redirection to add
 */
void		add_redir(t_redir **head, t_redir *new_redir);

/**
 * @brief Handles input redirection (<)
 * @param redir Redirection with filename
 * @return 0 on success, -1 on error
 */
int			handle_input_redir(t_redir *redir);

/**
 * @brief Handles output redirection (>, >>)
 * @param redir Redirection with filename
 * @return 0 on success, -1 on error
 */
int			handle_output_redir(t_redir *redir);

/**
 * @brief Handles heredoc redirection (<<)
 * @param redir Redirection with delimiter
 * @return 0 on success, -1 on error
 */
int			handle_heredoc(t_redir *redir, t_shell *shell);

/**
 * @brief Applies all redirections for command
 * @param redirs Redirection list to apply
 * @return 0 on success, -1 on error
 */
int			apply_redirections(t_redir *redirs, t_shell *shell);
int			open_redir_file(t_redir *redir);
void		close_all_fds(int *fds, int count);
int			count_redirs(t_redir *redirs);

/* ========================================================================== */
/*                            EXECUTOR - PIPELINE                            */
/* ========================================================================== */

/**
 * @brief Executes multi-command pipeline with pipes
 * @param shell Shell state with environment
 * @param cmds Command pipeline to execute
 * @return Exit status of last command
 */
int			execute_pipeline(t_shell *shell, t_cmd *cmds);
int			prepare_all_heredocs(t_cmd *cmds, t_shell *shell);
int			count_cmds(t_cmd *cmds);
void		update_underscore_pipe(t_shell *shell, char *cmd_name);

/**
 * @brief Executes single command with redirections
 * @param shell Shell state with environment
 * @param cmd Single command to execute
 * @return Command exit status
 */
int			execute_simple_cmd(t_shell *shell, t_cmd *cmd);

/**
 * @brief Executes command with redirections applied
 * @param shell Shell state
 * @param cmd Command to execute
 * @return Exit status of command
 */
int			exec_with_redir(t_shell *shell, t_cmd *cmd);

/**
 * @brief Executes an external command in a forked child process
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @return Exit status of command
 */
int			execute_external_cmd(t_shell *shell, t_cmd *cmd);

/**
 * @brief Prints signal termination message
 * @param sig Signal number
 */
void		print_signal_msg(int sig);

/**
 * @brief Waits for child and returns exit status
 * @param pid Child process ID
 * @param path Command path to free
 * @return Exit status
 */
int			wait_and_get_status(pid_t pid, char *path);

/**
 * @brief Converts environment linked list to array
 * @param env Environment linked list
 * @return NULL-terminated environment array
 */
char		**env_to_array_util(t_env *env);

/**
 * @brief Waits for all child processes
 * @param pids Array of process IDs
 * @param count Number of processes
 * @return Exit status of last process
 */
int			wait_for_pids(pid_t *pids, int count);

/**
 * @brief Closes all file descriptors >= 3
 */
void		close_unused_fds(void);

/**
 * @brief Restores stdin/stdout from backups
 * @param stdin_backup Backup file descriptor for stdin
 * @param stdout_backup Backup file descriptor for stdout
 */
void		restore_fds(int stdin_backup, int stdout_backup);
int			execute_redir_only(t_cmd *cmd, t_shell *shell);
int			prepare_heredocs(t_cmd *cmds, t_shell *shell);

/**
 * @brief Finds executable path for command
 * @param cmd Command name to find
 * @param env Environment with PATH variable
 * @return Full path to executable, NULL if not found
 */
char		*find_command_path(char *cmd, t_env *env);

/* ========================================================================== */
/*                            BUILTINS                                       */
/* ========================================================================== */

/**
 * @brief Checks if command is a builtin
 * @param cmd Command name to check
 * @return 1 if builtin, 0 otherwise
 */
int			is_builtin(char *cmd);

/**
 * @brief Executes builtin command
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @return Exit status of builtin
 */
int			execute_builtin(t_shell *shell, t_cmd *cmd);

/**
 * @brief Changes current directory (cd)
 * @param shell Shell state for PWD/OLDPWD
 * @param args Command arguments
 * @return 0 on success, 1 on error
 */
int			builtin_cd(t_shell *shell, char **args);

/**
 * @brief Prints arguments to stdout (echo)
 * @param args Command arguments (-n flag supported)
 * @return Always 0
 */
int			builtin_echo(char **args);

/**
 * @brief Displays command history (history)
 * @param args Command arguments (unused)
 * @return Always 0
 */
int			builtin_history(char **args);

/**
 * @brief Implements the '.' (source) builtin command
 * @param cmd Command structure
 * @param shell Shell state
 * @return 2 if no arguments, 0 otherwise
 */
int			builtin_source(t_cmd *cmd, t_shell *shell);

/**
 * @brief Prints environment variables (env)
 * @param env Environment linked list
 * @return 0 on success
 */
int			builtin_env(t_shell *shell, char **args);

/**
 * @brief Exits shell with status (exit)
 * @param shell Shell state for cleanup
 * @param args Command arguments (optional exit code)
 * @return Exit code
 */
int			builtin_exit(t_shell *shell, char **args);

/**
 * @brief Exports environment variables (export)
 * @param shell Shell state with environment
 * @param args Variables to export (KEY=VALUE)
 * @return 0 on success
 */
int			builtin_export(t_shell *shell, char **args);
int			is_valid_identifier(char *str);
int			handle_append_export(t_shell *shell, char *arg,
				char *key, char *equal);
void		print_all_exports(t_env *env);

/**
 * @brief Prints current working directory (pwd)
 * @return 0 on success, 1 on error
 */
int			builtin_pwd(void);

/**
 * @brief Unsets environment variables (unset)
 * @param shell Shell state with environment
 * @param args Variable names to unset
 * @return 0 on success
 */
int			builtin_unset(t_shell *shell, char **args);

/* ========================================================================== */
/*                            SIGNALS                                        */
/* ========================================================================== */

/**
 * @brief Sets up signal handlers for interactive mode
 */
void		setup_signals(void);

/**
 * @brief Sets up signal handlers for child processes
 */
void		setup_signals_child(void);

/**
 * @brief Sets up signal handlers during command execution
 */
void		setup_signals_exec(void);
void		process_line(t_shell *shell, char *line);
void		run_shell_loop(t_shell *shell);
char		*read_input(t_shell *shell);

/* ========================================================================== */
/*                            UTILITIES                                      */
/* ========================================================================== */

/**
 * @brief Gets environment variable value
 * @param env Environment linked list
 * @param key Variable name to search
 * @return Variable value, NULL if not found
 */
char		*get_env_value(t_env *env, char *key);

/**
 * @brief Sets environment variable value
 * @param env Pointer to environment list head
 * @param key Variable name
 * @param value Variable value
 */
void		set_env_value(t_env **env, char *key, char *value, int exported);

/**
 * @brief Unsets environment variable
 * @param env Pointer to environment list head
 * @param key Variable name to remove
 */
void		unset_env_value(t_env **env, char *key);

/**
 * @brief Frees entire environment linked list
 * @param env Environment list to free
 */
void		free_env(t_env *env);

/**
 * @brief Creates new environment node
 * @param key Variable name
 * @param value Variable value
 * @return Newly allocated environment node
 */
t_env		*create_env_node(char *key, char *value);

/**
 * @brief Initializes environment from envp
 * @param envp Environment array from main
 * @return Environment linked list
 */
t_env		*init_env(char **envp);
void		update_shlvl(t_env **env);

/**
 * @brief Safe malloc wrapper with error handling
 * @param size Number of bytes to allocate
 * @return Allocated memory, exits on failure
 */
void		*ft_malloc(size_t size);

/**
 * @brief Prints error message to stderr
 * @param msg Error message to print
 */
void		ft_error(char *msg);

/**
 * @brief Checks if character is a quote
 * @param c Character to check
 * @return 1 if single or double quote, 0 otherwise
 */
int			is_quote(char c);

/**
 * @brief Reads one line from pipe (stdin)
 * @return Line without newline, NULL on EOF
 */
char		*read_line_from_pipe(void);

/**
 * @brief Appends next line to current line
 * @param line Current line (freed)
 * @param next Next line (freed)
 * @return Joined line with newline between
 */
char		*append_line(char *line, char *next);

/**
 * @brief Checks if string is a valid identifier
 * @param str String to check
 * @return 1 if valid, 0 otherwise
 */
int			is_valid_identifier(char *str);

#endif
