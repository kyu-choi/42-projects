/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/07 00:00:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks if character is IFS
 * @param c Character to check
 * @return 1 if IFS, 0 otherwise
 */
static int	is_ifs_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * @brief Checks if string has leading whitespace
 * @param str String to check
 * @return 1 if has leading whitespace, 0 otherwise
 */
int	has_leading_ifs(char *str)
{
	if (!str || !*str)
		return (0);
	return (is_ifs_char(str[0]));
}

/**
 * @brief Checks if string has trailing whitespace
 * @param str String to check
 * @return 1 if has trailing whitespace, 0 otherwise
 */
int	has_trailing_ifs(char *str)
{
	int	len;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	return (is_ifs_char(str[len - 1]));
}
