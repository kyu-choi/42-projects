/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 22:06:36 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks if argument is valid flag (-n, -e, or -E)
 * @param arg Argument to check
 * @param flag_char Flag character ('n', 'e', or 'E')
 * @return 1 if valid flag, 0 otherwise
 * @details For -n, validates -n, -nn, -nnn... formats. For -e/-E, exact match
 */
static int	check_flag(char *arg, char flag_char)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != flag_char)
		return (0);
	if (flag_char == 'e' || flag_char == 'E')
		return (arg[2] == '\0');
	i = 2;
	while (arg[i])
	{
		if (arg[i] != flag_char)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Processes escape sequence and returns character
 * @param str String starting after backslash
 * @param i Pointer to current index (updated)
 * @return Character to output
 */
static char	process_escape(char *str, int *i)
{
	if (str[*i] == 'n')
	{
		(*i)++;
		return ('\n');
	}
	else if (str[*i] == 't')
	{
		(*i)++;
		return ('\t');
	}
	else if (str[*i] == 'r')
	{
		(*i)++;
		return ('\r');
	}
	else if (str[*i] == '\\')
	{
		(*i)++;
		return ('\\');
	}
	return ('\\');
}

/**
 * @brief Prints string with escape sequences interpreted
 * @param str String to print
 */
static void	print_with_escapes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i++;
			c = process_escape(str, &i);
			write(1, &c, 1);
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

/**
 * @brief Processes flags and returns starting argument index
 * @param args Command arguments
 * @param newline Pointer to newline flag
 * @param interpret_escapes Pointer to escape interpretation flag
 * @return Index of first non-flag argument
 */
static int	process_echo_flags(char **args, int *newline,
				int *interpret_escapes)
{
	int	i;

	i = 1;
	while (args[i] && (check_flag(args[i], 'n')
			|| check_flag(args[i], 'e') || check_flag(args[i], 'E')))
	{
		if (check_flag(args[i], 'n'))
			*newline = 0;
		if (check_flag(args[i], 'e'))
			*interpret_escapes = 1;
		if (check_flag(args[i], 'E'))
			*interpret_escapes = 0;
		i++;
	}
	return (i);
}

/**
 * @brief Implements echo builtin command
 * @param args Command arguments (args[0] = "echo")
 * @return Always 0
 * @details Supports -n, -e, and -E flags
 */
int	builtin_echo(char **args)
{
	int	i;
	int	newline;
	int	interpret_escapes;

	newline = 1;
	interpret_escapes = 0;
	i = process_echo_flags(args, &newline, &interpret_escapes);
	while (args[i])
	{
		if (interpret_escapes)
			print_with_escapes(args[i]);
		else
			ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
