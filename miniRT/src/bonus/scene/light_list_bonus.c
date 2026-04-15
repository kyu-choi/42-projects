/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file light_list_bonus.c
 * @brief Multi-light linked-list management.
 *
 * The bonus target allows multiple 'L' / 'l' lines in the .rt file.
 * Each parsed light is wrapped in a t_light_node and appended to
 * scene->lights.  The shader iterates this list to accumulate
 * per-light diffuse + specular contributions.
 */

/**
 * @brief Allocates a light-list node and copies the light data.
 *
 * @param light Light data to store.
 * @return New node, or NULL on malloc failure.
 */
static t_light_node	*rt_light_new(t_light light)
{
	t_light_node	*node;

	node = (t_light_node *)malloc(sizeof(t_light_node));
	if (!node)
		return (NULL);
	node->light = light;
	node->next = NULL;
	return (node);
}

/**
 * @brief Appends a light to the scene's multi-light list.
 *
 * @param scene Scene whose lights list is extended.
 * @param light Light data to add.
 * @return 1 on success; 0 on malloc failure.
 */
int	rt_light_add(t_scene *scene, t_light light)
{
	t_light_node	*node;
	t_light_node	*cur;

	node = rt_light_new(light);
	if (!node)
		return (0);
	if (!scene->lights)
		scene->lights = node;
	else
	{
		cur = scene->lights;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
	return (1);
}

/**
 * @brief Frees the entire light linked list.
 *
 * @param lights Head of the list (may be NULL).
 */
void	rt_free_lights(t_light_node *lights)
{
	t_light_node	*next;

	while (lights)
	{
		next = lights->next;
		free(lights);
		lights = next;
	}
}
