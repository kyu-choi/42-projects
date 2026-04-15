/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:06:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks for input redirection tokens (< or <<)
 * @param str Input string
 * @param i Pointer to current index (updated if match)
 * @param head Pointer to token list head
 * @return 1 if redirection found and added, 0 otherwise
 * @details Handles both < (input) and << (heredoc)
 */
int	check_redir_token(char *str, int *i, t_token **head)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			add_token_to_list_util(head, create_token(TOKEN_REDIR_HEREDOC,
					ft_strdup("<<")));
			*i += 2;
		}
		else
		{
			add_token_to_list_util(head, create_token(TOKEN_REDIR_IN,
					ft_strdup("<")));
			(*i)++;
		}
		return (1);
	}
	return (0);
}

/**
 * @brief Checks for FD redirection (digit> or digit>>)
 * @param str Input string
 * @param i Pointer to current index
 * @param head Pointer to token list head
 * @return 1 if FD redir found, 0 otherwise
 */
static int	check_digit_redir(char *str, int *i, t_token **head)
{
	int	start;

	start = *i;
	if (!ft_isdigit(str[*i]))
		return (0);
	(*i)++;
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		add_token_to_list_util(head, create_token(TOKEN_REDIR_APPEND,
				ft_substr(str, start, 3)));
		*i += 2;
		return (1);
	}
	else if (str[*i] == '>')
	{
		add_token_to_list_util(head, create_token(TOKEN_REDIR_OUT,
				ft_substr(str, start, 2)));
		(*i)++;
		return (1);
	}
	*i = start;
	return (0);
}

/**
 * @brief Checks for output redirection tokens (> or >>)
 * @param str Input string
 * @param i Pointer to current index (updated if match)
 * @param head Pointer to token list head
 * @return 1 if redirection found and added, 0 otherwise
 * @details Handles both > (output) and >> (append)
 */
int	check_redir_token2(char *str, int *i, t_token **head)
{
	if (ft_isdigit(str[*i]) && (str[*i + 1] == '>'))
		return (check_digit_redir(str, i, head));
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			add_token_to_list_util(head, create_token(TOKEN_REDIR_APPEND,
					ft_strdup(">>")));
			*i += 2;
		}
		else if (str[*i + 1] == '|')
		{
			add_token_to_list_util(head, create_token(TOKEN_REDIR_OUT,
					ft_strdup(">")));
			*i += 2;
		}
		else
		{
			add_token_to_list_util(head, create_token(TOKEN_REDIR_OUT,
					ft_strdup(">")));
			(*i)++;
		}
		return (1);
	}
	return (0);
}

/**
 * @brief Checks for pipe token (|)
 * @param str Input string
 * @param i Pointer to current index (updated if match)
 * @param head Pointer to token list head
 * @return 1 if pipe found and added, 0 otherwise
 */
int	check_pipe_token(char *str, int *i, t_token **head)
{
	if (str[*i] == '|' && str[*i + 1] != '|')
	{
		add_token_to_list_util(head, create_token(TOKEN_PIPE,
				ft_strdup("|")));
		(*i)++;
		return (1);
	}
	return (0);
}

/**
 * @brief Checks for semicolon token at current position
 * @param str Input string
 * @param i Pointer to current index (updated if semicolon found)
 * @param head Pointer to token list head
 * @return 1 if semicolon found and added, 0 otherwise
 */
int	check_semicolon_token(char *str, int *i, t_token **head)
{
	if (str[*i] == ';')
	{
		add_token_to_list_util(head, create_token(TOKEN_SEMICOLON,
				ft_strdup(";")));
		(*i)++;
		return (1);
	}
	return (0);
}
