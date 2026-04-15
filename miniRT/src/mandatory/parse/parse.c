/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file parse.c
 * @brief Top-level scene parsing pipeline.
 *
 * Parse pipeline:
 * 1. rt_scene_init: zero out the scene struct
 * 2. rt_read_file: read entire .rt file into a string
 * 3. rt_parse_text: split by newline, call rt_parse_line per line
 * 4. rt_validate_scene: ensure A/C/L set exactly once, objs exist,
 *    camera basis is valid
 *
 * On any failure the scene is freed and 0 is returned. The caller
 * (rt_init) does not need to free anything on failure.
 */

/**
 * @brief Zeroes scene state. objs=NULL, set=0, default colors.
 */
static void	rt_scene_init(t_scene *scene)
{
	scene->objs = NULL;
	scene->amb.set = 0;
	scene->cam.set = 0;
	scene->light.set = 0;
	scene->amb.ratio = 0.0;
	scene->amb.color = rt_color(1.0, 1.0, 1.0);
	scene->light.ratio = 0.0;
	scene->light.color = rt_color(1.0, 1.0, 1.0);
}

/**
 * @brief Parses txt line-by-line. Stops on first error.
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
 * @brief Validates A/C/L set once, objs non-empty, camera basis valid.
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
 * @brief Full parse: read file, parse lines, validate. Frees on failure.
 * @return 1 on success, 0 on error
 */
int	rt_parse_scene(char *path, t_scene *scene)
{
	char	*txt;

	rt_scene_init(scene);
	txt = rt_read_file(path);
	if (!txt)
		return (rt_error("Cannot read scene file"));
	if (!rt_parse_text(txt, scene))
	{
		free(txt);
		rt_free_scene(scene);
		return (0);
	}
	free(txt);
	if (!rt_validate_scene(scene))
	{
		rt_free_scene(scene);
		return (0);
	}
	return (1);
}
