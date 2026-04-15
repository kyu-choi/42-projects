/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:32:40 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:33:09 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"

int		ft_printf(const char *format, ...);

char	*utoa_lowhex(unsigned int i);
char	*utoa_uphex(unsigned int i);
char	*lltoa_hex(unsigned long long i);
int		printchar(va_list args);
int		printlowhex(va_list args);
int		printuphex(va_list args);
int		printint(va_list args);
int		printpoint(va_list args);
int		printstr(va_list args);
int		printunsigned(va_list args);
char	*utoa(unsigned int num);

#endif
