/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_bonus.c
 * @brief Top-level scene parser: read file → split lines → validate.
 *
 * Parse pipeline:
 *   1. rt_init_scene — zero all fields, set defaults.
 *   2. rt_read_file  — load entire .rt file.
 *   3. Per-line: rt_parse_line dispatches by identifier.
 *   4. Validate: A, C, and L must each be set exactly once.
 */

/**
 * @brief Zero scene state; set defaults.
 */
static void	rt_scene_init(t_scene *scene)
{
	scene->objs = NULL;
	scene->lights = NULL;
	scene->amb.set = 0;
	scene->cam.set = 0;
	scene->light.set = 0;
	scene->amb.ratio = 0.0;
	scene->amb.color = rt_color(1.0, 1.0, 1.0);
	scene->light.ratio = 0.0;
	scene->light.color = rt_color(1.0, 1.0, 1.0);
}

/**
 * @brief Parse txt line-by-line; modify txt (nul-terminate lines).
 * @return 1 on success; 0 on first parse error.
 */
static int	rt_parse_text(char *txt, t_scene *scene)
{
	char	*line;
	char	*cur;

	cur = txt;
	while (*cur)
	{
		line = cur;
		while (*cur && *cur != '\n')
			cur++;
		if (*cur == '\n')
		{
			*cur = '\0';
			cur++;
		}
		if (!rt_parse_line(line, scene))
			return (0);
	}
	return (1);
}

/**
 * @brief Ensure A/C/L set once; objs exist; camera basis valid.
 * @return 1 on success; 0 on error (calls rt_error).
 */
static int	rt_validate_scene(t_scene *scene)
{
	if (!scene->amb.set || !scene->cam.set || !scene->light.set)
		return (rt_error("A/C/L must be set exactly once"));
	if (!scene->objs)
		return (rt_error("No object in scene"));
	if (!rt_setup_camera(&scene->cam))
		return (rt_error("Invalid camera basis"));
	return (1);
}

/**
 * @brief Free txt and scene; return 0. Used on parse failure.
 */
static int	rt_parse_fail(char *txt, t_scene *scene)
{
	free(txt);
	rt_free_scene(scene);
	return (0);
}

/**
 * @brief Load and parse .rt file; init scene; validate.
 * @param path Path to .rt file.
 * @param scene Scene to fill.
 * @return 1 on success; 0 on error.
 */
int	rt_parse_scene(char *path, t_scene *scene)
{
	char	*txt;

	rt_scene_init(scene);
	txt = rt_read_file(path);
	if (!txt)
		return (rt_error("Cannot read scene file"));
	if (!rt_parse_text(txt, scene))
		return (rt_parse_fail(txt, scene));
	free(txt);
	if (!rt_validate_scene(scene))
	{
		rt_free_scene(scene);
		return (0);
	}
	return (1);
}
