/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_BONUS_H
# define MINI_RT_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"

/**
 * @file mini_rt_bonus.h
 * @brief Bonus target: public types and function prototypes.
 *
 * Extends the mandatory header with:
 *   - OBJ_CONE type and cone intersection/parsing prototypes.
 *   - t_light_node linked list for multi-light support.
 *   - Per-object material fields: checker, specular, bump.
 *   - Per-hit material fields: specular, shininess.
 *   - Reflection in rt_trace_ray (depth-limited recursion).
 */

/* -------------------------------------------------------------------------- */
/* Window / math constants                                                    */
/* -------------------------------------------------------------------------- */
# define WIN_W 1280
# define WIN_H 720
# define EPS 1e-6
# define STEP_MOVE 0.8
# define STEP_ROT 0.0872664626
# define STEP_SIZE 0.5

/* -------------------------------------------------------------------------- */
/* Object identifiers used in parser + hit dispatch                           */
/* -------------------------------------------------------------------------- */
# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_CYLINDER 3
# define OBJ_CONE 4
# define OBJ_HYPERBOLOID 5
# define OBJ_PARABOLOID 6

# define EVENT_DESTROY 17
# define EVENT_CONFIGURE 22

# define MASK_CONFIGURE 0

/* -------------------------------------------------------------------------- */
/* Key mapping per platform (macOS / Linux)                                   */
/* -------------------------------------------------------------------------- */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_Q 12
#  define KEY_E 14
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_TAB 48
#  define KEY_I 34
#  define KEY_J 38
#  define KEY_K 40
#  define KEY_L 37
#  define KEY_U 32
#  define KEY_O 31
#  define KEY_T 17
#  define KEY_G 5
#  define KEY_F 3
#  define KEY_H 4
#  define KEY_R 15
#  define KEY_Y 16
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_C 8
#  define KEY_V 9
#  define KEY_B 11
#  define KEY_N 45
#  define KEY_M 46
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_P 35
#  define KEY_1 18
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_Q 113
#  define KEY_E 101
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_TAB 65289
#  define KEY_I 105
#  define KEY_J 106
#  define KEY_K 107
#  define KEY_L 108
#  define KEY_U 117
#  define KEY_O 111
#  define KEY_T 116
#  define KEY_G 103
#  define KEY_F 102
#  define KEY_H 104
#  define KEY_R 114
#  define KEY_Y 121
#  define KEY_Z 122
#  define KEY_X 120
#  define KEY_C 99
#  define KEY_V 118
#  define KEY_B 98
#  define KEY_N 110
#  define KEY_M 109
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define KEY_P 112
#  define KEY_1 49
# endif

typedef struct s_mlx_win_stub
{
	void	*winid;
}	t_mlx_win_stub;

typedef struct s_ns_rect
{
	double	x;
	double	y;
	double	w;
	double	h;
}	t_ns_rect;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_color;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

typedef struct s_obj
{
	int				type;
	t_vec3			center;
	t_vec3			axis;
	t_vec3			point;
	double			radius;
	double			height;
	t_color			color;
	int				checker;
	double			checker_scale;
	t_color			checker_color;
	double			specular;
	double			shininess;
	int				bump;
	double			bump_scale;
	double			bump_strength;
	struct s_obj	*next;
}	t_obj;

typedef struct s_ambient
{
	int		set;
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	int		set;
	t_vec3	pos;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_light_node
{
	t_light				light;
	struct s_light_node	*next;
}	t_light_node;

typedef struct s_camera
{
	int		set;
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
	t_vec3	right;
	t_vec3	up;
}	t_camera;

typedef struct s_scene
{
	t_ambient		amb;
	t_light			light;
	t_light_node	*lights;
	t_camera		cam;
	t_obj			*objs;
}	t_scene;

typedef struct s_hit
{
	int		hit;
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
	double	specular;
	double	shininess;
}	t_hit;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_rt
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene			scene;
	t_obj			*selected_obj;
	t_light_node	*selected_light;
	int				win_w;
	int				win_h;
	int				show_ui;
	int				show_axes;
}	t_rt;

/* -------------------------------------------------------------------------- */
/* API groups                                                                 */
/* -------------------------------------------------------------------------- */
void		rt_putstr_fd(char *s, int fd);
int			rt_error(char *msg);
void		rt_free_objects(t_obj *obj);
void		rt_free_scene(t_scene *scene);
int			rt_close(t_rt *rt);

t_vec3		rt_vec3(double x, double y, double z);
t_vec3		rt_add(t_vec3 a, t_vec3 b);
t_vec3		rt_sub(t_vec3 a, t_vec3 b);
t_vec3		rt_scale(t_vec3 v, double s);
double		rt_dot(t_vec3 a, t_vec3 b);

double		rt_len(t_vec3 v);
t_vec3		rt_norm(t_vec3 v);
t_vec3		rt_cross(t_vec3 a, t_vec3 b);
t_vec3		rt_neg(t_vec3 v);
double		rt_clamp(double value, double min, double max);
t_vec3		rt_rotate_axis(t_vec3 v, t_vec3 axis, double angle);

t_color		rt_color(double r, double g, double b);
t_color		rt_color_add(t_color a, t_color b);
t_color		rt_color_mul(t_color c, double s);
t_color		rt_color_mod(t_color a, t_color b);
int			rt_color_to_int(t_color c);

char		*rt_read_file(char *path);
int			rt_parse_scene(char *path, t_scene *scene);
void		rt_skip_spaces(char **s);
int			rt_parse_double(char **s, double *out);
int			rt_parse_int(char **s, int *out);
int			rt_parse_vec3(char **s, t_vec3 *v);
int			rt_parse_color(char **s, t_color *c);
int			rt_parse_norm_vec(char **s, t_vec3 *v);
int			rt_parse_end(char *s);
int			rt_parse_line(char *line, t_scene *scene);
int			rt_parse_obj_options(char **p, t_obj *obj);

int			rt_parse_ambient(char *s, t_scene *scene);
int			rt_parse_camera(char *s, t_scene *scene);
int			rt_parse_light(char *s, t_scene *scene);
int			rt_parse_light_extra(char *s, t_scene *scene);
int			rt_parse_sphere(char *s, t_scene *scene);
int			rt_parse_plane(char *s, t_scene *scene);
int			rt_parse_cylinder(char *s, t_scene *scene);
int			rt_parse_cone(char *s, t_scene *scene);
int			rt_parse_hyperboloid(char *s, t_scene *scene);
int			rt_parse_paraboloid(char *s, t_scene *scene);

t_obj		*rt_obj_new(int type);
int			rt_obj_add(t_scene *scene, t_obj *obj);

int			rt_light_add(t_scene *scene, t_light light);
void		rt_free_lights(t_light_node *lights);

int			rt_init(t_rt *rt, char *path);
int			rt_init_mlx(t_rt *rt);
int			rt_key_press(int key, t_rt *rt);
int			rt_expose(t_rt *rt);
int			rt_on_resize(int w, int h, t_rt *rt);
void		rt_enable_window_resize(t_rt *rt);
int			rt_poll_resize(t_rt *rt);
void		rt_destroy_mlx(t_rt *rt);
int			rt_control_camera(t_rt *rt, int key);
int			rt_control_scene(t_rt *rt, int key);

void		rt_put_pixel(t_img *img, int x, int y, int color);
void		rt_render(t_rt *rt);
void		rt_draw_debug_axes(t_rt *rt);
void		rt_draw_axis_labels(t_rt *rt);

int			rt_setup_camera(t_camera *cam);
t_ray		rt_ray_from_pixel(t_rt *rt, int x, int y);
int			rt_hit_scene(t_scene *scene, t_ray ray, t_hit *hit);
int			rt_hit_sphere(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_hit_plane(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_hit_cylinder_side(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_hit_cylinder(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_hit_cone(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_hit_hyperboloid(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_hit_paraboloid(t_obj *obj, t_ray ray, t_hit *hit);
int			rt_in_shadow(t_scene *scene, t_vec3 p, t_vec3 n);
int			rt_in_shadow_light(t_scene *scene, t_vec3 p,
				t_vec3 n, t_light *light);
t_color		rt_get_object_color(t_obj *obj, t_vec3 point);
void		rt_apply_hit_material(t_hit *hit, t_obj *obj);
t_color		rt_shade_hit(t_scene *scene, t_hit *hit);
t_color		rt_trace_ray(t_scene *scene, t_ray ray);

#endif
