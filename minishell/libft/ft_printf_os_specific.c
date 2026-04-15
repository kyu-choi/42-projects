/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_os_specific.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:35:09 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// macOS version for '%'
int	handle_percent_macos(t_flags *flags)
{
	return (apply_char_padding('%', flags));
}

// Linux version for '%'
int	handle_percent_linux(t_flags *flags)
{
	(void)flags;
	if (write(1, "%", 1) == -1)
		return (-1);
	return (1);
}

// macOS version for 's' with NULL
char	*get_processed_string_and_len_macos(char *str, t_flags *flags,
			size_t *len)
{
	if (!str)
		str = "(null)";
	*len = ft_strlen(str);
	if (flags->precision >= 0 && (size_t)flags->precision < *len)
		*len = flags->precision;
	return (str);
}

// Linux version for 's' with NULL
char	*get_processed_string_and_len_linux(char *str, t_flags *flags,
			size_t *len)
{
	if (!str)
	{
		if (flags->precision >= 0 && flags->precision < 6)
			str = "";
		else
			str = "(null)";
	}
	*len = ft_strlen(str);
	if (flags->precision >= 0 && (size_t)flags->precision < *len)
		*len = flags->precision;
	return (str);
}
