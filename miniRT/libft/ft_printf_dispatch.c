/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dispatch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:33:16 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Dispatches the print job to the appropriate handler based on the specifier.
// It ats as a router, delegating the task to specialized functions.
int	dispatch_print(t_flags *flags, va_list ap)
{
	if (flags->specifier == 'c')
		return (handle_char(flags, ap));
	if (flags->specifier == '%')
		return (handle_percent(flags));
	if (flags->specifier == 's')
		return (handle_string(flags, ap));
	if (flags->specifier == 'p')
		return (handle_pointer(flags, ap));
	if (flags->specifier == 'd' || flags->specifier == 'i')
		return (handle_decimal(flags, ap));
	if (flags->specifier == 'u')
		return (handle_unsigned(flags, ap));
	if (flags->specifier == 'x' || flags->specifier == 'X')
		return (handle_hex(flags, ap));
	return (0);
}
