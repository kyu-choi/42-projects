/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_macos_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 00:05:43 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"
#include <objc/message.h>
#include <objc/runtime.h>

#define NS_WINDOW_STYLE_RESIZABLE 8UL

static void	*rt_msg_id(void *obj, const char *name)
{
	SEL	sel;

	if (!obj)
		return (NULL);
	sel = sel_registerName(name);
	return (((void *(*)(void *, SEL))objc_msgSend)(obj, sel));
}

static unsigned long	rt_msg_ulong(void *obj, const char *name)
{
	SEL	sel;

	if (!obj)
		return (0);
	sel = sel_registerName(name);
	return (((unsigned long (*)(void *, SEL))objc_msgSend)(obj, sel));
}

static int	rt_view_size(void *view, int *w, int *h)
{
	t_ns_rect	rect;
	SEL			sel;

	if (!view)
		return (0);
	sel = sel_registerName("frame");
	rect = ((t_ns_rect (*)(void *, SEL))objc_msgSend)(view, sel);
	*w = (int)rect.w;
	*h = (int)rect.h;
	return (*w > 0 && *h > 0);
}

void	rt_enable_window_resize(t_rt *rt)
{
	t_mlx_win_stub	*mlx_win;
	void			*ns_win;
	SEL				set_sel;
	unsigned long	mask;

	if (!rt || !rt->win)
		return ;
	mlx_win = (t_mlx_win_stub *)rt->win;
	ns_win = rt_msg_id(mlx_win->winid, "win");
	if (!ns_win)
		return ;
	mask = rt_msg_ulong(ns_win, "styleMask");
	mask |= NS_WINDOW_STYLE_RESIZABLE;
	set_sel = sel_registerName("setStyleMask:");
	((void (*)(void *, SEL, unsigned long))objc_msgSend)(ns_win, set_sel, mask);
}

int	rt_poll_resize(t_rt *rt)
{
	t_mlx_win_stub	*mlx_win;
	void			*ns_win;
	void			*view;
	int				w;
	int				h;

	if (!rt || !rt->win)
		return (0);
	mlx_win = (t_mlx_win_stub *)rt->win;
	ns_win = rt_msg_id(mlx_win->winid, "win");
	view = rt_msg_id(ns_win, "contentView");
	if (!rt_view_size(view, &w, &h))
		return (0);
	if (w != rt->win_w || h != rt->win_h)
		rt_on_resize(w, h, rt);
	return (0);
}
