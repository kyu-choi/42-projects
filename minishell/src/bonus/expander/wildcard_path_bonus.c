/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_path_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 02:41:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"
#include <sys/stat.h>

/**
 * @brief Builds full path from directory and filename
 * @param dir_base Base directory
 * @param name Entry name
 * @return Full path or NULL
 */
static char	*build_dir_path(const char *dir_base, const char *name)
{
	char	*temp;
	char	*result;

	if (dir_base[0] == '.' && dir_base[1] == '\0')
		return (ft_strdup(name));
	temp = ft_strjoin(dir_base, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, name);
	free(temp);
	return (result);
}

/**
 * @brief Checks if a directory entry is a directory
 * @param dir_path Base directory path
 * @param name Entry name
 * @return 1 if directory, 0 otherwise
 */
int	is_directory(const char *dir_path, const char *name)
{
	struct stat	statbuf;
	char		*full_path;
	int			result;

	full_path = build_dir_path(dir_path, name);
	if (!full_path)
		return (0);
	result = (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode));
	free(full_path);
	return (result);
}

/**
 * @brief Counts directories matching pattern
 * @param dir Directory to search
 * @param pattern Directory pattern
 * @return Number of matching directories
 */
int	count_matching_dirs(DIR *dir, const char *pattern, const char *base)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if ((pattern[0] == '.' || entry->d_name[0] != '.')
			&& match_pattern(pattern, entry->d_name)
			&& is_directory(base, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	return (count);
}

/**
 * @brief Fills array with matching directory paths
 * @param dir Directory to search
 * @param pattern Directory pattern
 * @param base Base directory path
 * @param dirs Array to fill
 */
void	fill_matching_dirs(DIR *dir, const char *pattern,
		const char *base, char **dirs)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if ((pattern[0] == '.' || entry->d_name[0] != '.')
			&& match_pattern(pattern, entry->d_name)
			&& is_directory(base, entry->d_name))
		{
			dirs[i] = build_dir_path(base, entry->d_name);
			if (dirs[i])
				i++;
		}
		entry = readdir(dir);
	}
	dirs[i] = NULL;
}
