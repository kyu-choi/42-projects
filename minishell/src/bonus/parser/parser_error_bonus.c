/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:30:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 11:29:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Prints syntax error with specific token
 * @param token Token string that caused the error
 */
void	print_syntax_error_bonus(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd((char *)token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

/**
 * @brief Prints syntax error for empty parentheses
 */
void	print_empty_paren_error_bonus(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
}

/**
 * @brief Prints syntax error for unmatched parenthesis
 */
void	print_unmatched_paren_error_bonus(void)
{
	ft_putstr_fd("minishell: syntax error: unmatched `('\n", 2);
}
