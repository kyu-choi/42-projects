/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Counts number of environment variables
 * @param env Environment linked list
 * @return Number of environment variables
 */
static int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value && env->exported)
			count++;
		env = env->next;
	}
	return (count);
}

/**
 * @brief Fills environment array from linked list
 * @param envp Array to fill (must be pre-allocated)
 * @param env Environment linked list
 * @details Each entry formatted as "KEY=VALUE"
 */
static void	fill_env_array(char **envp, t_env *env)
{
	char	*temp;
	int		i;

	i = 0;
	while (env)
	{
		if (env->value && env->exported)
		{
			temp = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(temp, env->value);
			free(temp);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
}

/**
 * @brief Converts environment list to NULL-terminated array
 * @param env Environment linked list
 * @return Newly allocated environment array (KEY=VALUE format)
 * @details Used for execve, caller must free array
 */
char	**env_to_array_util(t_env *env)
{
	char	**envp;
	int		count;

	count = count_env(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	fill_env_array(envp, env);
	return (envp);
}
