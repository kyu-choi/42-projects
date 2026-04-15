/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 11:29:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints syntax error with specific token
 * @param token Token string that caused the error (e.g., "|", "&&")
 * @details Outputs: "minishell: syntax error near unexpected token `token'"
 */
void	print_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	if (token && *token)
	{
		ft_putstr_fd(" `", 2);
		ft_putstr_fd((char *)token, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}
