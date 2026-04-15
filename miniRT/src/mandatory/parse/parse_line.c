/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file parse_line.c
 * @brief Per-line parsing: extract identifier, dispatch to element parser.
 *
 * Supported identifiers (mandatory):
 * - Single-char: A (ambient), C (camera), L (light)
 * - Two-char: sp (sphere), pl (plane), cy (cylinder)
 *
 * After extracting the identifier the rest of the line is passed
 * to the appropriate element parser (rt_parse_ambient, etc.).
 *
 * @note Empty lines and lines containing only whitespace are
 *       silently accepted (return 1).
 */

/**
 * @brief Dispatches to ambient/camera/light/sphere/plane/cylinder parser.
 */
static int	rt_dispatch(char *id, char *s, t_scene *scene)
{
	if (ft_streq(id, "A"))
		return (rt_parse_ambient(s, scene));
	if (ft_streq(id, "C"))
		return (rt_parse_camera(s, scene));
	if (ft_streq(id, "L"))
		return (rt_parse_light(s, scene));
	if (ft_streq(id, "sp"))
		return (rt_parse_sphere(s, scene));
	if (ft_streq(id, "pl"))
		return (rt_parse_plane(s, scene));
	if (ft_streq(id, "cy"))
		return (rt_parse_cylinder(s, scene));
	return (rt_error("Unknown identifier"));
}

/**
 * @brief Reads two-char id (a,b). Advances *s on match.
 */
static int	rt_read_pair(char **s, char id[3], char a, char b)
{
	if ((*s)[0] != a || (*s)[1] != b)
		return (0);
	id[0] = a;
	id[1] = b;
	*s = *s + 2;
	return (1);
}

/**
 * @brief Reads A/C/L or sp/pl/cy. Writes id, advances *s.
 */
static int	rt_read_id(char **s, char id[3])
{
	id[0] = 0;
	id[1] = 0;
	id[2] = 0;
	if (**s == 'A' || **s == 'C' || **s == 'L')
	{
		id[0] = **s;
		(*s)++;
		return (1);
	}
	if (rt_read_pair(s, id, 's', 'p'))
		return (1);
	if (rt_read_pair(s, id, 'p', 'l'))
		return (1);
	if (rt_read_pair(s, id, 'c', 'y'))
		return (1);
	return (0);
}

/**
 * @brief Parses one line: skip spaces, read id, dispatch. Empty lines ok.
 * @return 1 on success or empty, 0 on error
 */
int	rt_parse_line(char *line, t_scene *scene)
{
	char	*s;
	char	id[3];

	s = line;
	rt_skip_spaces(&s);
	if (!*s)
		return (1);
	if (!rt_read_id(&s, id))
		return (rt_error("Invalid line identifier"));
	if (*s && !ft_isspace(*s))
		return (rt_error("Identifier separator missing"));
	return (rt_dispatch(id, s, scene));
}
