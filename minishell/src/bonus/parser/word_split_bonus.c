/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/07 00:00:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks if character is IFS (Internal Field Separator)
 * @param c Character to check
 * @return 1 if IFS (space, tab, newline), 0 otherwise
 */
static int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * @brief Skips IFS characters
 * @param str String pointer
 * @return Updated pointer after IFS characters
 */
static char	*skip_ifs(char *str)
{
	while (*str && is_ifs(*str))
		str++;
	return (str);
}

/**
 * @brief Gets length of next word
 * @param str String pointer
 * @return Length of word (until next IFS or end)
 */
static int	get_word_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_ifs(str[len]))
		len++;
	return (len);
}

/**
 * @brief Counts words in string separated by IFS
 * @param str String to count words in
 * @return Number of words
 */
static int	count_words(char *str)
{
	int	count;

	count = 0;
	str = skip_ifs(str);
	while (*str)
	{
		count++;
		str += get_word_len(str);
		str = skip_ifs(str);
	}
	return (count);
}

/**
 * @brief Splits string into words by IFS characters
 * @param str String to split
 * @return NULL-terminated array of words, or NULL if empty/error
 * @details Splits by space, tab, newline. Empty string returns NULL.
 */
char	**split_words(char *str)
{
	char	**words;
	int		count;
	int		i;
	int		len;

	if (!str || !*str)
		return (NULL);
	count = count_words(str);
	if (count == 0)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	str = skip_ifs(str);
	while (i < count)
	{
		len = get_word_len(str);
		words[i++] = ft_substr(str, 0, len);
		str += len;
		str = skip_ifs(str);
	}
	words[i] = NULL;
	return (words);
}
