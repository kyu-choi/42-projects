/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file camera.c
 * @brief Camera coordinate frame setup and per-pixel ray generation.
 *
 * The camera uses a standard look-at model:
 * - dir: forward direction (from .rt file)
 * - right: perpendicular to dir and world-up (cross product)
 * - up: perpendicular to right and dir (second cross product)
 *
 * RAY GENERATION ALGORITHM (pinhole camera):
 * For each pixel (x, y) on the screen:
 * 1. Map pixel to normalized device coordinates (NDC) in [-1, 1]
 * 2. Scale by FOV tangent and aspect ratio
 * 3. Combine: ray_dir = dir + px*right + py*up
 * 4. Normalize the resulting direction
 *
 * This produces a perspective projection where FOV controls how
 * wide the view frustum is (larger FOV = wider angle).
 */

/**
 * @brief Picks an initial "world up" vector for the camera basis.
 *
 * If the camera direction is nearly parallel to (0,1,0), using it
 * as the up reference would produce a degenerate cross product
 * (zero-length right vector = gimbal lock). In that case we fall
 * back to (0,0,1) as the reference.
 *
 * @param dir Camera forward direction (unit vector).
 * @return Reference up vector: (0,1,0) or (0,0,1) if near-parallel.
 */
static t_vec3	rt_world_up(t_vec3 dir)
{
	if (fabs(dir.y) > 0.99)
		return (rt_vec3(0.0, 0.0, 1.0));
	return (rt_vec3(0.0, 1.0, 0.0));
}

/**
 * @brief Builds orthonormal camera basis (right, up) from dir.
 *
 * Algorithm:
 * 1. Normalize dir (safety)
 * 2. Choose a world-up reference that avoids gimbal lock
 * 3. right = normalize(dir x up_ref)
 * 4. up = normalize(right x dir)
 *
 * @param cam Camera to set up (dir must be set; right/up are filled).
 * @return 1 on success; 0 if dir is parallel to up_ref (degenerate).
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

/**
 * @brief Converts degrees to radians.
 */
static double	rt_deg_to_rad(double degree)
{
	return (degree * 0.017453292519943295);
}

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
