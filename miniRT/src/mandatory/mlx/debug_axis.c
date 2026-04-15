/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_axis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#define AXIS_LEN 3.0
#define DEG2RAD 0.017453292519943295

static t_vec3	rt_project(t_rt *rt, t_vec3 world)
{
	t_vec3	d;
	t_vec3	proj;
	double	scale;
	double	aspect;

	d = rt_sub(world, rt->scene.cam.pos);
	proj.z = rt_dot(d, rt->scene.cam.dir);
	if (proj.z < EPS)
		return (rt_vec3(-1, -1, -1));
	scale = tan(rt->scene.cam.fov * 0.5 * DEG2RAD);
	aspect = (double)rt->win_w / (double)rt->win_h;
	proj.x = (rt_dot(d, rt->scene.cam.right)
			/ (proj.z * aspect * scale) + 1.0) * 0.5 * rt->win_w;
	proj.y = (1.0 - rt_dot(d, rt->scene.cam.up)
			/ (proj.z * scale)) * 0.5 * rt->win_h;
	return (proj);
}

static void	rt_draw_line(t_img *img, t_vec3 a, t_vec3 b, int color)
{
	int		steps;
	double	xi;
	double	yi;
	int		i;

	steps = (int)fmax(fabs(b.x - a.x), fabs(b.y - a.y));
	if (steps == 0)
		return ;
	xi = (b.x - a.x) / steps;
	yi = (b.y - a.y) / steps;
	i = -1;
	while (++i <= steps)
		rt_put_pixel(img, (int)(a.x + i * xi),
			(int)(a.y + i * yi), color);
}

static void	rt_draw_one_axis(t_rt *rt, t_vec3 tip_3d, int color)
{
	t_vec3	origin_2d;
	t_vec3	tip_2d;

	origin_2d = rt_project(rt, rt_vec3(0, 0, 0));
	tip_2d = rt_project(rt, tip_3d);
	if (origin_2d.z < 0 || tip_2d.z < 0)
		return ;
	rt_draw_line(&rt->img, origin_2d, tip_2d, color);
}

void	rt_draw_debug_axes(t_rt *rt)
{
	rt_draw_one_axis(rt, rt_vec3(AXIS_LEN, 0, 0), 0xFF0000);
	rt_draw_one_axis(rt, rt_vec3(0, AXIS_LEN, 0), 0x00FF00);
	rt_draw_one_axis(rt, rt_vec3(0, 0, AXIS_LEN), 0x0000FF);
}

void	rt_draw_axis_labels(t_rt *rt)
{
	t_vec3	tip;

	tip = rt_project(rt, rt_vec3(AXIS_LEN, 0, 0));
	if (tip.z > 0)
		mlx_string_put(rt->mlx, rt->win,
			(int)tip.x + 4, (int)tip.y, 0xFF0000, "X");
	tip = rt_project(rt, rt_vec3(0, AXIS_LEN, 0));
	if (tip.z > 0)
		mlx_string_put(rt->mlx, rt->win,
			(int)tip.x + 4, (int)tip.y, 0x00FF00, "Y");
	tip = rt_project(rt, rt_vec3(0, 0, AXIS_LEN));
	if (tip.z > 0)
		mlx_string_put(rt->mlx, rt->win,
			(int)tip.x + 4, (int)tip.y, 0x0000FF, "Z");
}
