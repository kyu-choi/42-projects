/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 02:41:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Expands pattern in specific directory
 * @param dir_path Directory path
 * @param pattern Filename pattern
 * @return Array of matched files with paths
 */
char	**expand_pattern_in_dir(const char *dir_path, const char *pattern)
{
	DIR		*dir;
	char	**files;
	int		count;

	count = count_matches_in_dir(dir_path, pattern);
	if (count == 0)
		return (NULL);
	files = malloc(sizeof(char *) * (count + 1));
	if (!files)
		return (NULL);
	dir = opendir(dir_path);
	if (!dir)
	{
		free(files);
		return (NULL);
	}
	fill_matched_files_with_path(dir, dir_path, pattern, files);
	closedir(dir);
	return (files);
}

/**
 * @brief Extracts directory path from pattern
 * @param pattern Pattern with possible directory (e.g., "dir / *.c")
 * @return Directory path or "." if no directory
 */
char	*get_dir_from_pattern(const char *pattern)
{
	char	*last_slash;
	char	*dir;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup("."));
	dir = ft_substr(pattern, 0, last_slash - pattern);
	if (!dir || dir[0] == '\0')
	{
		free(dir);
		return (ft_strdup("/"));
	}
	return (dir);
}

/**
 * @brief Extracts filename pattern from full pattern
 * @param pattern Full pattern (e.g., "dir / *.c")
 * @return Filename part (e.g., "*.c")
 */
const char	*get_filename_from_pattern(const char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (pattern);
	return (last_slash + 1);
}

/**
 * @brief Expands wildcard pattern to list of matching files
 * 
 * @param pattern Wildcard pattern (e.g., "*.c" or "dir / *.c")
 * @return char** Array of matched filenames (NULL-terminated)
 */
char	**expand_pattern(const char *pattern)
{
	char		**files;
	char		*dir_path;
	const char	*filename_pattern;

	dir_path = get_dir_from_pattern(pattern);
	filename_pattern = get_filename_from_pattern(pattern);
	if (ft_strchr(dir_path, '*'))
	{
		files = expand_with_dir_wildcard(dir_path, filename_pattern);
		free(dir_path);
		return (files);
	}
	files = expand_simple_pattern(dir_path, filename_pattern);
	free(dir_path);
	if (files)
		sort_string_array(files);
	return (files);
}

/**
 * @brief Expands simple pattern without directory wildcards
 * @param dir_path Directory path
 * @param pattern Filename pattern
 * @return Array of matched files
 */
char	**expand_simple_pattern(const char *dir_path, const char *pattern)
{
	DIR		*dir;
	char	**files;
	int		count;

	count = count_matches_in_dir(dir_path, pattern);
	if (count == 0)
		return (NULL);
	files = malloc(sizeof(char *) * (count + 1));
	if (!files)
		return (NULL);
	dir = opendir(dir_path);
	if (!dir)
	{
		free(files);
		return (NULL);
	}
	fill_matched_files_with_path(dir, dir_path, pattern, files);
	closedir(dir);
	return (files);
}
