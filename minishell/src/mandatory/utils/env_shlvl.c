/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Updates or creates SHLVL environment variable
 * @param env Pointer to environment list head
 * @details Creates SHLVL with value "1" if not present (mandatory version)
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
	(void)node;
}
