/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_array_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 02:41:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Counts total arguments after expansion
 * @param args Original argument array
 * @param expansions Expansion arrays
 * @return Total argument count
 */
int	count_total_args(char **args, char ***expansions)
{
	int	total;
	int	i;
	int	j;

	total = 0;
	i = 0;
	while (args[i])
	{
		if (expansions[i])
		{
			j = 0;
			while (expansions[i][j])
			{
				total++;
				j++;
			}
		}
		else
			total++;
		i++;
	}
	return (total);
}

/**
 * @brief Builds result array from expansions
 * @param args Original arguments
 * @param exp Expansion arrays
 * @param total Total count
 * @return Newly allocated result array
 */
char	**build_result(char **args, char ***exp, int total)
{
	char	**result;
	int		idx;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (total + 1));
	if (!result)
		return (NULL);
	idx = 0;
	i = 0;
	while (args[i])
	{
		if (exp[i])
		{
			j = 0;
			while (exp[i][j])
				result[idx++] = exp[i][j++];
		}
		else
			result[idx++] = ft_strdup(args[i]);
		i++;
	}
	result[idx] = NULL;
	return (result);
}

/**
 * @brief Creates expansion arrays for each argument
 * @param args Arguments to expand
 * @param count Argument count
 * @return Array of expansion results
 */
char	***create_expansions(char **args, int count)
{
	char	***expansions;
	int		i;

	expansions = malloc(sizeof(char **) * count);
	if (!expansions)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		if (ft_strchr(args[i], '*'))
			expansions[i] = expand_pattern(args[i]);
		else
			expansions[i] = NULL;
	}
	return (expansions);
}

/**
 * @brief Expands wildcards in argument array
 * @param args Original argument array
 * @return Array with wildcards expanded (or original if no expansion)
 */
char	**expand_wildcards(char **args)
{
	char	***expansions;
	char	**result;
	int		count;
	int		total;

	if (!args || !args[0])
		return (args);
	count = 0;
	while (args[count])
		count++;
	expansions = create_expansions(args, count);
	if (!expansions)
		return (args);
	total = count_total_args(args, expansions);
	result = build_result(args, expansions, total);
	free_expansions(expansions, count);
	if (result)
		return (result);
	return (args);
}

/**
 * @brief Frees all expansion arrays
 * @param expansions Expansion arrays to free
 * @param count Number of expansions
 */
void	free_expansions(char ***expansions, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		if (expansions[i])
			free(expansions[i]);
	free(expansions);
}
