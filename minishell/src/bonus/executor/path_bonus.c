/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
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
 * @brief Tries to find executable in specific directory
 * @param dir Directory path
 * @param cmd Command name
 * @return Full path if executable found, NULL otherwise
 * @details Checks execute permission with access(X_OK)
 */
static char	*try_path(char *dir, char *cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

/**
 * @brief Searches for command in PATH directories
 * @param cmd Command name
 * @param path_env PATH environment variable value
 * @return Full path if found, NULL otherwise
 * @details Splits PATH by ':' and tries each directory
 */
static char	*search_in_path(char *cmd, char *path_env)
{
	char	**dirs;
	char	*result;
	int		i;

	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		result = try_path(dirs[i], cmd);
		if (result)
		{
			ft_free_split(dirs);
			return (result);
		}
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

/**
 * @brief Finds full path for command
 * @param cmd Command name or path
 * @param env Environment list
 * @return Full path (newly allocated), NULL if not found
 * @details Handles absolute/relative paths and PATH search
 */
char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;

	if (!cmd || !*cmd)
		return (NULL);
	if ((ft_strncmp(cmd, ".", 2) == 0 && cmd[1] == '\0')
		|| (ft_strncmp(cmd, "..", 3) == 0 && cmd[2] == '\0'))
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (ft_strdup(cmd));
	return (search_in_path(cmd, path_env));
}
