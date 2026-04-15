/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_line_bonus.c
 * @brief Line-level parsing: identifier dispatch (bonus).
 *
 * Supported identifiers: A (ambient), C (camera), L (main light),
 * l (extra light), sp (sphere), pl (plane), cy (cylinder), co (cone).
 * Empty / whitespace-only lines are silently skipped.
 */

/**
 * @brief Dispatch to parser by identifier.
 * @param id 1-2 char id (A,C,L,l,sp,pl,cy,co).
 * @param s Rest of line after id.
 * @param scene Scene to fill.
 * @return 1 on success; 0 on error.
 */
static int	rt_dispatch(char *id, char *s, t_scene *scene)
{
	if (ft_streq(id, "A"))
		return (rt_parse_ambient(s, scene));
	if (ft_streq(id, "C"))
		return (rt_parse_camera(s, scene));
	if (ft_streq(id, "L"))
		return (rt_parse_light(s, scene));
	if (ft_streq(id, "l"))
		return (rt_parse_light_extra(s, scene));
	if (ft_streq(id, "sp"))
		return (rt_parse_sphere(s, scene));
	if (ft_streq(id, "pl"))
		return (rt_parse_plane(s, scene));
	if (ft_streq(id, "cy"))
		return (rt_parse_cylinder(s, scene));
	if (ft_streq(id, "co"))
		return (rt_parse_cone(s, scene));
	if (ft_streq(id, "hy"))
		return (rt_parse_hyperboloid(s, scene));
	if (ft_streq(id, "pa"))
		return (rt_parse_paraboloid(s, scene));
	return (rt_error("Unknown identifier"));
}

/**
 * @brief Read two-char id (sp,pl,cy,co); advance *s.
 * @return 1 if matched; 0 otherwise.
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
 * @brief Extract line identifier into id[3]; advance *s.
 * @return 1 if valid id; 0 otherwise.
 */
static int	rt_read_id(char **s, char id[3])
{
	id[0] = 0;
	id[1] = 0;
	id[2] = 0;
	if (**s == 'A' || **s == 'C' || **s == 'L' || **s == 'l')
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
	if (rt_read_pair(s, id, 'c', 'o'))
		return (1);
	if (rt_read_pair(s, id, 'h', 'y'))
		return (1);
	if (rt_read_pair(s, id, 'p', 'a'))
		return (1);
	return (0);
}

/**
 * @brief Parse one .rt line; skip empty; dispatch by id.
 * @param line Nul-terminated line (may be modified).
 * @param scene Scene to update.
 * @return 1 on success; 0 on error.
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
