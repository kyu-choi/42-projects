/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file error.c
 * @brief Error reporting, resource cleanup, and program exit.
 *
 * All error paths print "Error\n" followed by a descriptive message to
 * stderr (fd 2), matching the 42 subject requirement.  Cleanup helpers
 * walk the object list and reset scene flags so that no heap block is
 * leaked on exit.
 */

/**
 * @brief Writes a string to a file descriptor.
 *
 * A minimal ft_putstr replacement that avoids pulling in libft for the
 * error-reporting path.
 *
 * @param s  String to write (no-op if NULL).
 * @param fd Target file descriptor (typically 2 for stderr).
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
 * @brief Prints an error message to stderr and returns failure.
 *
 * Format: "Error\n<msg>\n".  Returning 0 lets callers write
 * `return (rt_error("…"))` as a one-liner failure path.
 *
 * @param msg Descriptive error message (may be NULL).
 * @return Always 0 (failure).
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
 * @brief Frees every node in the object linked list.
 *
 * @param obj Head of the list (may be NULL).
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
 * @brief Frees all objects and resets environment flags.
 *
 * Called before re-parsing or on exit.  Resetting the `set` flags
 * ensures that a fresh parse can detect duplicate A / C / L lines.
 *
 * @param scene Scene to clean (no-op if NULL).
 */
void	rt_free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	rt_free_objects(scene->objs);
	scene->objs = NULL;
	scene->amb.set = 0;
	scene->cam.set = 0;
	scene->light.set = 0;
}

/**
 * @brief Destroys all resources and exits the program.
 *
 * Called by the MLX close hook (window X button / ESC).  Cleanup order:
 * MLX resources first (image → window → display), then scene memory.
 *
 * @param rt Application context to tear down.
 * @return Never returns (calls exit(0)).
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
