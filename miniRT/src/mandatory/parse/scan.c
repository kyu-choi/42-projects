/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file scan.c
 * @brief Low-level scanner: whitespace skip and end-of-line check.
 *
 * These helpers are used by all element parsers to advance past
 * spaces between tokens and to verify that no trailing garbage
 * remains after the expected fields.
 */

/**
 * @brief Advances *s past all leading whitespace characters.
 * @param s Pointer to the current parse position (updated in place).
 */
void	rt_skip_spaces(char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

/**
 * @brief Checks that only whitespace remains on the line.
 *
 * This is called after the last expected field to reject lines
 * with extra tokens (e.g., "sp 0,0,0 5 255,0,0 GARBAGE").
 *
 * @param s Current parse position.
 * @return 1 if line is clean; 0 if non-whitespace remains.
 */
int	rt_parse_end(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (*s)
		return (0);
	return (1);
}
