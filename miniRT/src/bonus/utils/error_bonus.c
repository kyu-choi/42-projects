/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file error_bonus.c
 * @brief Error reporting, resource cleanup, and program exit (bonus).
 *
 * Extends the mandatory error module by also freeing the multi-light
 * linked list (scene->lights) in rt_free_scene.
 */

/**
 * @brief Write string to fd (no-op if s is NULL).
 * @param s String to write.
 * @param fd File descriptor (typically 2 for stderr).
 */
void	rt_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = (int)ft_strlen(s);
	if (len > 0)
		write(fd, s, len);
}

/**
 * @brief Print "Error\\n" + msg to stderr and return 0.
 * @param msg Optional message; may be NULL.
 * @return 0 always (convenience for early-return).
 */
int	rt_error(char *msg)
{
	rt_putstr_fd("Error\n", 2);
	if (msg)
		rt_putstr_fd(msg, 2);
	rt_putstr_fd("\n", 2);
	return (0);
}

/**
 * @brief Free linked list of objects.
 * @param obj Head of object list; may be NULL.
 */
void	rt_free_objects(t_obj *obj)
{
	t_obj	*next;

	while (obj)
	{
		next = obj->next;
		free(obj);
		obj = next;
	}
}

/**
 * @brief Free objs, lights; reset amb/cam/light flags.
 * @param scene Scene to clear; may be NULL.
 */
void	rt_free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	rt_free_objects(scene->objs);
	rt_free_lights(scene->lights);
	scene->objs = NULL;
	scene->lights = NULL;
	scene->amb.set = 0;
	scene->cam.set = 0;
	scene->light.set = 0;
}

/**
 * @brief Cleanup MLX, scene; exit(0). Used as destroy hook.
 * @param rt Runtime context.
 * @return 0 (unused; exit never returns).
 */
int	rt_close(t_rt *rt)
{
	if (rt)
	{
		rt_destroy_mlx(rt);
		rt_free_scene(&rt->scene);
	}
	exit(0);
	return (0);
}
