/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/05 23:50:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks for file descriptor redirection (>&숫자)
 * @param str Input string
 * @param i Pointer to current index (updated if match)
 * @param head Pointer to token list head
 * @return 1 if >&digit pattern found and added as WORD, 0 otherwise
 * @details Treats >&digit as a WORD token to avoid syntax errors
 */
int	check_fd_redir(char *str, int *i, t_token **head)
{
	int	j;

	if (str[*i] != '>' || str[*i + 1] != '&')
		return (0);
	j = *i + 2;
	if (!ft_isdigit(str[j]))
		return (0);
	while (ft_isdigit(str[j]))
		j++;
	add_token_to_list_util(head, create_token(TOKEN_WORD,
			ft_substr(str, *i, j - *i)));
	*i = j;
	return (1);
}
