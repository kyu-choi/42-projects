/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/05 23:20:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Compares two strings for sorting
 * @param a First string
 * @param b Second string
 * @return Negative if a < b, positive if a > b, 0 if equal
 */
static int	compare_strings(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i])
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (a[i] - b[i]);
}

/**
 * @brief Sorts string array alphabetically (bubble sort)
 * @param arr Array of strings to sort
 */
void	sort_string_array(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	if (!arr || !arr[0])
		return ;
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[j + 1])
		{
			if (compare_strings(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
