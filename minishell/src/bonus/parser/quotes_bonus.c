/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Finds closing quote position
 * @param str String starting at opening quote
 * @param quote Quote character to match
 * @return Index of closing quote, -1 if not found
 */
int	find_closing_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i);
	return (-1);
}

/**
 * @brief Copies content between quotes to result
 * @param str Source string
 * @param i Pointer to current index (at opening quote)
 * @param result Destination buffer
 * @param j Pointer to result index
 * @return 1 if quote closed successfully, 0 otherwise
 */
static int	copy_quoted_content(char *str, int *i, char *result, int *j)
{
	char	quote;
	int		start_i;
	int		start_j;

	quote = str[*i];
	start_i = (*i);
	start_j = (*j);
	(*i)++;
	while (str[*i] && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
	{
		(*i)++;
		return (1);
	}
	*i = start_i;
	*j = start_j;
	return (0);
}

/**
 * @brief Removes all quotes from string
 * @param str String with quotes
 * @return Newly allocated string without quotes
 */
char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && copy_quoted_content(str, &i, result, &j))
			continue ;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

/**
 * @brief Skips over a quoted section in string
 * @param str Input string
 * @param i Pointer to current index
 * @param quote Quote character (single or double)
 * @return Quote char if unclosed, 0 if properly closed
 */
static int	skip_quoted_section(char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && str[*i] == '\\' && str[*i + 1])
			(*i) += 2;
		else
			(*i)++;
	}
	if (!str[*i])
		return (quote);
	return (0);
}

/**
 * @brief Checks for unclosed quotes in string
 * @param str Input string
 * @return Quote char if unclosed, 0 if closed
 */
int	get_unclosed_quote(char *str)
{
	int		i;
	char	unclosed;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			continue ;
		}
		if (is_quote(str[i]))
		{
			unclosed = skip_quoted_section(str, &i, str[i]);
			if (unclosed)
				return (unclosed);
		}
		if (str[i])
			i++;
	}
	return (0);
}
