/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:50:56 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/01/07 20:43:20 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_split - Split a string by a delimiter into an array of 
 * 	strings
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *  	char **ft_split(const char *s, char c);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *  	The ft_split() function allocates (with malloc) and returns an array 
 * 	of strings obtained by splitting 's' using the character 'c' as a 
 * 	delimiter. The array ends with a NULL pointer. Consecutive delimiters 
 * 	are treated as separate splits, and empty strings are not included in 
 * 	the result.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The array of strings resulting from the split, or NULL if the 
 * 	allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static size_t	count_words(const char *s, char c);
static size_t	get_word_len(const char *s, char c, size_t *start);
static int		populate_words(const char *s, char c, char **words,
					size_t word_count);

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	if (populate_words(s, c, words, word_count) == -1)
		return (NULL);
	words[word_count] = NULL;
	return (words);
}

/*
 * count_words - Uses `get_next_word` to skip delimiters and count how many
 * 	words exist in the string 's'.
 */
static size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	start;
	size_t	len;

	count = 0;
	start = 0;
	while (s[start])
	{
		len = get_word_len(s, c, &start);
		if (len > 0)
		{
			++count;
			start += len;
		}
	}
	return (count);
}

/*
 * get_word_len - Moves '*start' forward past any delimiters 'c', then counts
 * 	how many characters until the next delimiter or the end of the string.
 * 	Returns the length. The substring [*start, *start + length) represents
 * 	one word.
 */
size_t	get_word_len(const char *s, char c, size_t *start)
{
	size_t	len;

	len = 0;
	while (s[*start] && s[*start] == c)
		++(*start);
	while (s[*start + len] && s[*start + len] != c)
		++len;
	return (len);
}

/*
 * populate_words: Allocates memory for each word, copies it, and places it
 * 	into the 'words' array. If any allocation fails, frees all allocated
 * 	blocks (including 'words' itself) and returns -1.
 * 	On success, returns 0.
 */
static int	populate_words(const char *s, char c, char **words,
				size_t word_count)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*word;

	i = 0;
	start = 0;
	while (i < word_count)
	{
		len = get_word_len(s, c, &start);
		word = (char *)malloc(sizeof(char) * (len + 1));
		if (!word)
		{
			while (i > 0)
				free(words[--i]);
			free(words);
			return (-1);
		}
		ft_strlcpy(word, &s[start], len + 1);
		words[i++] = word;
		start += len;
	}
	return (0);
}
