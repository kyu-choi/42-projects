/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl_bonus.c                                  :+:      :+:    :+:   */
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
 * @brief Checks if string is a valid numeric value
 * @param str String to check
 * @return 1 if numeric (with optional +/- prefix), 0 otherwise
 */
static int	is_numeric_value(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Updates existing SHLVL environment node
 * @param node SHLVL environment node to update
 * @details Increments numeric value or sets to 1 if invalid
 */
static void	update_existing_shlvl_bonus(t_env *node)
{
	int		level;
	char	*value;

	if (!is_numeric_value(node->value))
		level = 1;
	else
		level = ft_atoi(node->value) + 1;
	value = ft_itoa(level);
	if (!value)
		return ;
	free(node->value);
	node->value = value;
}

/**
 * @brief Updates or creates SHLVL environment variable
 * @param env Pointer to environment list head
 * @details Increments SHLVL or creates it with value "1" if not present
 */
void	update_shlvl(t_env **env)
{
	t_env	*node;

	if (!env)
		return ;
	node = *env;
	while (node && ft_strncmp(node->key, "SHLVL", 6) != 0)
		node = node->next;
	if (!node)
	{
		node = create_env_node("SHLVL", "1");
		if (node)
		{
			node->next = *env;
			*env = node;
		}
		return ;
	}
	update_existing_shlvl_bonus(node);
}
