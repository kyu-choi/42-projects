/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_bonus.c                                   :+:      :+:    :+:   */
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
 * @brief Creates new environment node
 * @param key Variable name
 * @param value Variable value
 * @return Newly allocated environment node
 */
t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->exported = 1;
	node->next = NULL;
	return (node);
}

/**
 * @brief Adds one environment entry from envp array
 * @param head Pointer to environment list head
 * @param current Pointer to current tail of list
 * @param envp_entry Single environment string (KEY=VALUE)
 * @details Splits on =, creates node, appends to list
 */
static void	add_env_entry(t_env **head, t_env **current, char *envp_entry)
{
	t_env	*new_node;
	char	*equal;

	equal = ft_strchr(envp_entry, '=');
	if (!equal)
		return ;
	*equal = '\0';
	new_node = create_env_node(envp_entry, equal + 1);
	if (new_node)
	{
		if (!*head)
			*head = new_node;
		else
			(*current)->next = new_node;
		*current = new_node;
	}
	*equal = '=';
}

/**
 * @brief Ensures a default environment variable exists
 * @param head Pointer to environment list head
 * @param key Variable key name
 * @param value Default value to set if variable doesn't exist
 */
static void	ensure_default_var(t_env **head, char *key, char *value)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return ;
		tmp = tmp->next;
	}
	if (!*head)
		*head = create_env_node(key, value);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_env_node(key, value);
	}
}

/**
 * @brief Initializes environment linked list from envp
 * @param envp Environment array from main
 * @return Head of environment linked list
 * @details Parses each KEY=VALUE entry into linked list
 */
t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;
	char	cwd[1024];

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_entry(&head, &current, envp[i]);
		i++;
	}
	ensure_default_var(&head, "OLDPWD", NULL);
	if (getcwd(cwd, sizeof(cwd)))
		ensure_default_var(&head, "PWD", cwd);
	return (head);
}

/**
 * @brief Frees entire environment linked list
 * @param env Environment list to free
 * @details Frees all keys, values, and nodes
 */
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
