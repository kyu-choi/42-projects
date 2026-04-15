/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
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
 * @brief Checks if string contains wildcard character
 * @param str String to check
 * @return 1 if wildcard found, 0 otherwise
 */
int	check_wildcard(const char *str)
{
	int		in_quote;
	char	quote_char;
	int		i;

	in_quote = 0;
	quote_char = 0;
	i = 0;
	while (str && str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
		{
			in_quote = 1;
			quote_char = str[i];
		}
		else if (in_quote && str[i] == quote_char)
			in_quote = 0;
		else if (!in_quote && str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Checks if wildcard pattern matches filename (simple * matching)
 * 
 * @param pattern Pattern string (e.g., "*.c")
 * @param str String to compare against (filename)
 * @return int 1 if matches, 0 otherwise
 */
int	match_pattern(const char *pattern, const char *str)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '\x01')
	{
		if (*str == '*')
			return (match_pattern(pattern + 1, str + 1));
		return (0);
	}
	if (*pattern == '*')
	{
		if (match_pattern(pattern + 1, str))
			return (1);
		if (*str && match_pattern(pattern, str + 1))
			return (1);
		return (0);
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

/**
 * @brief Counts files matching pattern in specific directory
 * 
 * @param dir_path Directory path to search
 * @param pattern Wildcard pattern (filename only)
 * @return int Number of matched files
 */
int	count_matches_in_dir(const char *dir_path, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(dir_path);
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if ((pattern[0] == '.' || entry->d_name[0] != '.')
			&& match_pattern(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

/**
 * @brief Builds path for matched file
 * @param dir_path Directory path
 * @param name File name
 * @return Full path
 */
static char	*build_matched_path(const char *dir_path, const char *name)
{
	char	*temp;
	char	*result;

	if (dir_path[0] == '.' && dir_path[1] == '\0')
		return (ft_strdup(name));
	temp = ft_strjoin(dir_path, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, name);
	free(temp);
	return (result);
}

/**
 * @brief Fills array with filenames matching pattern from directory with paths
 * @param dir Opened directory
 * @param dir_path Directory path for building full paths
 * @param pattern Pattern string (filename only)
 * @param files Array to fill
 */
void	fill_matched_files_with_path(DIR *dir, const char *dir_path,
		const char *pattern, char **files)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if ((pattern[0] == '.' || entry->d_name[0] != '.')
			&& match_pattern(pattern, entry->d_name))
		{
			files[i] = build_matched_path(dir_path, entry->d_name);
			if (files[i])
				i++;
		}
		entry = readdir(dir);
	}
	files[i] = NULL;
}
