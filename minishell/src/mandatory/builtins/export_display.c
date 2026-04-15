/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 01:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Counts number of environment variables
 * @param env Environment linked list
 * @return Number of environment variables
 */
static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * @brief Compares two environment nodes by key
 * @param a First environment node
 * @param b Second environment node
 * @return Negative if a < b, 0 if equal, positive if a > b
 */
static int	compare_env_keys(t_env *a, t_env *b)
{
	size_t	len_a;
	size_t	len_b;
	size_t	max;

	len_a = ft_strlen(a->key);
	len_b = ft_strlen(b->key);
	max = len_a;
	if (len_b > len_a)
		max = len_b;
	return (ft_strncmp(a->key, b->key, max + 1));
}

/**
 * @brief Sorts environment array by key (bubble sort)
 * @param array Array of environment node pointers
 * @param count Number of elements in array
 * @details In-place sort using bubble sort algorithm
 */
static void	sort_env_array(t_env **array, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (compare_env_keys(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Prints a single environment variable in export format
 * @param env Environment variable to print
 * @details Format: declare -x KEY="VALUE" with escaped special characters
 */
static void	print_entry(t_env *env)
{
	int	i;

	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (!env->value)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	ft_putstr_fd("=\"", 1);
	i = 0;
	while (env->value[i])
	{
		if (env->value[i] == '"' || env->value[i] == '\\'
			|| env->value[i] == '$' || env->value[i] == '`')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(env->value[i], 1);
		i++;
	}
	ft_putstr_fd("\"\n", 1);
}

/**
 * @brief Prints all environment variables in export format
 * @param env Environment variable list
 * @details Sorts variables alphabetically before printing
 */
void	print_all_exports(t_env *env)
{
	t_env	**array;
	int		count;
	int		i;

	count = count_env_vars(env);
	if (count == 0)
		return ;
	array = malloc(sizeof(t_env *) * count);
	if (!array)
		return ;
	i = 0;
	while (env)
	{
		if (ft_strncmp(env->key, "_", 2) != 0)
			array[i++] = env;
		env = env->next;
	}
	count = i;
	sort_env_array(array, count);
	i = 0;
	while (i < count)
		print_entry(array[i++]);
	free(array);
}
