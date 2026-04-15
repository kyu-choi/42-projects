/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file scan_bonus.c
 * @brief Low-level scanning helpers: skip whitespace, check end.
 *
 * rt_skip_spaces advances the cursor past spaces/tabs.
 * rt_parse_end returns 1 only if all remaining characters are
 * whitespace — rejects trailing garbage after the last token.
 */

/**
 * @brief Advance *s past leading spaces (ft_isspace).
 * @param s Pointer to string; modified in place.
 */
void	rt_skip_spaces(char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

/**
 * @brief Check string has only trailing whitespace (valid end).
 * @param s Nul-terminated string.
 * @return 1 if rest is whitespace/NUL; 0 if extra chars.
 */
int	rt_parse_end(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (*s)
		return (0);
	return (1);
}
