/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 00:49:03 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Gets value of environment variable
 * @param env Environment linked list
 * @param key Variable name to search for
 * @return Variable value, NULL if not found
 */
char	*get_env_value(t_env *env, char	*key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, key_len + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Updates value of existing environment node
 * @param node Environment node to update
 * @param value New value (duplicated)
 * @param exported Export flag (1=exported, 0=not exported, -1=no change)
 * @details Frees old value and sets new one
 */
static void	update_env_val(t_env *node, char	*value, int exported)
{
	if (value)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	if (exported >= 0)
		node->exported = exported;
}

/**
 * @brief Appends new environment node to list
 * @param env Pointer to environment list head
 * @param last Last node in list
 * @param params Array: [0]=key, [1]=value
 * @param exported Export flag (1=exported, 0=not exported)
 */
static void	append_env_node(t_env **env, t_env *last,
				char **params, int exported)
{
	t_env	*new_node;

	new_node = create_env_node(params[0], params[1]);
	if (!new_node)
		return ;
	new_node->exported = exported;
	if (!*env)
		*env = new_node;
	else if (last)
		last->next = new_node;
}

/**
 * @brief Sets or updates environment variable
 * @param env Pointer to environment list head
 * @param key Variable name
 * @param value Variable value
 * @param exported Export flag (1=exported, 0=not exported)
 * @details Updates existing variable or creates new one
 */
void	set_env_value(t_env **env, char	*key, char	*value, int exported)
{
	t_env	*curr;
	char	*params[2];
	size_t	len;

	len = ft_strlen(key);
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len + 1) == 0)
		{
			update_env_val(curr, value, exported);
			return ;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	params[0] = key;
	params[1] = value;
	append_env_node(env, curr, params, exported);
}

/**
 * @brief Removes environment variable from list
 * @param env Pointer to environment list head
 * @param key Variable name to remove
 * @details Frees the node and its key/value
 */
void	unset_env_value(t_env **env, char	*key)
{
	t_env	*current;
	t_env	*prev;
	size_t	key_len;

	key_len = ft_strlen(key);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, key_len + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
