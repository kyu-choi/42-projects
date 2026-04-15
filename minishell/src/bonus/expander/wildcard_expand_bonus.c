/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand_bonus.c                            :+:      :+:    :+:   */
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
 * @brief Expands directories matching pattern
 * @param dir_base Base directory to search in
 * @param dir_pattern Directory pattern
 * @return Array of matched directory paths
 */
char	**expand_directories(const char *dir_base, const char *dir_pattern)
{
	DIR		*dir;
	char	**dirs;
	int		count;

	dir = opendir(dir_base);
	if (!dir)
		return (NULL);
	count = count_matching_dirs(dir, dir_pattern, dir_base);
	if (count == 0)
	{
		closedir(dir);
		return (NULL);
	}
	dirs = malloc(sizeof(char *) * (count + 1));
	if (!dirs)
	{
		closedir(dir);
		return (NULL);
	}
	rewinddir(dir);
	fill_matching_dirs(dir, dir_pattern, dir_base, dirs);
	closedir(dir);
	return (dirs);
}

/**
 * @brief Counts total files from all directories
 * @param dirs Directory array
 * @param pattern Filename pattern
 * @return Total file count
 */
static int	count_total_files(char **dirs, const char *pattern)
{
	char	**files;
	int		i;
	int		j;
	int		total;

	total = 0;
	i = 0;
	while (dirs[i])
	{
		files = expand_pattern_in_dir(dirs[i], pattern);
		if (files)
		{
			j = 0;
			while (files[j])
			{
				total++;
				j++;
			}
			ft_free_split(files);
		}
		i++;
	}
	return (total);
}

/**
 * @brief Collects all files from directories
 * @param dirs Directory array
 * @param pattern Filename pattern
 * @param all_files Output array
 * @return Number of files collected
 */
static int	collect_all_files(char **dirs, const char *pattern,
		char **all_files)
{
	char	**files;
	int		i;
	int		j;
	int		total;

	total = 0;
	i = 0;
	while (dirs[i])
	{
		files = expand_pattern_in_dir(dirs[i], pattern);
		if (files)
		{
			j = 0;
			while (files[j])
			{
				all_files[total] = files[j];
				total++;
				j++;
			}
			free(files);
		}
		i++;
	}
	return (total);
}

/**
 * @brief Expands pattern with directory wildcards
 * @param dir_path Directory path (may contain wildcards)
 * @param filename_pattern Filename pattern
 * @return Array of all matched files
 */
char	**expand_with_dir_wildcard(const char *dir_path,
		const char *filename_pattern)
{
	char	**dirs;
	char	**all_files;
	int		total;

	dirs = expand_directories(".", dir_path);
	if (!dirs || !dirs[0])
		return (dirs);
	total = count_total_files(dirs, filename_pattern);
	if (total == 0)
	{
		ft_free_split(dirs);
		return (NULL);
	}
	all_files = malloc(sizeof(char *) * (total + 1));
	if (!all_files)
	{
		ft_free_split(dirs);
		return (NULL);
	}
	total = collect_all_files(dirs, filename_pattern, all_files);
	all_files[total] = NULL;
	ft_free_split(dirs);
	sort_string_array(all_files);
	return (all_files);
}
