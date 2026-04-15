/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file camera_bonus.c
 * @brief Camera basis computation and per-pixel ray generation (bonus).
 *
 * The camera uses a pinhole model.  rt_setup_camera builds the
 * right/up basis from cam.dir + a world-up hint.  rt_ray_from_pixel
 * converts pixel (x, y) to normalised device coordinates, applies
 * the FOV scaling, and returns a direction in world space.
 */

/**
 * @brief World up for camera; avoid gimbal when dir near Y.
 */
static t_vec3	rt_world_up(t_vec3 dir)
{
	if (fabs(dir.y) > 0.99)
		return (rt_vec3(0.0, 0.0, 1.0));
	return (rt_vec3(0.0, 1.0, 0.0));
}

/**
 * @brief Build right/up from dir; orthonormal basis.
 * @return 1 on success; 0 if dir degenerate.
 */
int	rt_setup_camera(t_camera *cam)
{
	t_vec3	up_ref;

	cam->dir = rt_norm(cam->dir);
	up_ref = rt_world_up(cam->dir);
	cam->right = rt_cross(cam->dir, up_ref);
	if (rt_len(cam->right) < EPS)
		return (0);
	cam->right = rt_norm(cam->right);
	cam->up = rt_cross(cam->right, cam->dir);
	cam->up = rt_norm(cam->up);
	return (1);
}

static double	rt_deg_to_rad(double degree)
{
	return (degree * 0.017453292519943295);
}

/**
 * @brief Primary ray from camera through pixel (x,y).
 * @return Ray origin and normalized direction.
 */
t_ray	rt_ray_from_pixel(t_rt *rt, int x, int y)
{
	t_ray	ray;
	double	scale;
	double	aspect;
	double	px;
	double	py;

	aspect = (double)rt->win_w / (double)rt->win_h;
	scale = tan(rt_deg_to_rad(rt->scene.cam.fov * 0.5));
	px = (2.0 * ((double)x + 0.5) / (double)rt->win_w - 1.0)
		* aspect * scale;
	py = (1.0 - 2.0 * ((double)y + 0.5) / (double)rt->win_h) * scale;
	ray.orig = rt->scene.cam.pos;
	ray.dir = rt_add(rt->scene.cam.dir, rt_scale(rt->scene.cam.right, px));
	ray.dir = rt_add(ray.dir, rt_scale(rt->scene.cam.up, py));
	ray.dir = rt_norm(ray.dir);
	return (ray);
}
