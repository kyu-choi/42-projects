/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
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
 * @brief Checks if string is a valid number
 * @param str String to validate
 * @return 1 if valid number (with optional +/- prefix), 0 otherwise
 */
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Initializes overflow check variables
 * @param str String to parse
 * @param i Pointer to index (set after whitespace and sign)
 * @param sign Pointer to sign (1 or -1)
 */
static void	init_overflow(const char *str, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
		*sign = -1;
	if (str[*i] == '+' || str[*i] == '-')
		(*i)++;
}

/**
 * @brief Checks if string will overflow long long
 * @param str String to check
 * @return 1 if overflow, 0 otherwise
 * @details Uses LLONG_MAX/MIN cutoff values
 */
static int	check_overflow(const char *str)
{
	unsigned long long	res;
	unsigned long long	cutoff;
	int					cutlim;
	int					sign;
	int					i;

	init_overflow(str, &i, &sign);
	res = 0;
	cutoff = 9223372036854775807ULL;
	if (sign == -1)
		cutoff = 9223372036854775808ULL;
	while (str[i] >= '0' && str[i] <= '9')
	{
		cutlim = str[i] - '0';
		if (res > (cutoff - cutlim) / 10)
			return (1);
		res = res * 10 + cutlim;
		i++;
	}
	return (0);
}

/**
 * @brief Converts string to long long
 * @param str String to convert
 * @return Converted long long value
 * @details Similar to atoll but without overflow protection
 */
static long long	ft_atoll(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((long long)(res * sign));
}

/**
 * @brief Implements exit builtin command
 * @param shell Shell state with last exit status
 * @param args Command arguments (args[1] = optional exit code)
 * @return Never returns (calls exit()), or 1 if too many arguments
 * @details Validates numeric argument and exits with code modulo 256
 */
int	builtin_exit(t_shell *shell, char **args)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (!args[1])
		exit(shell->last_exit_status);
	if (!is_valid_number(args[1]) || check_overflow(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoll(args[1]);
	exit((unsigned char)exit_code);
}
