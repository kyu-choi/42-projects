/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:51:58 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	ch;

	if (!s)
		return (NULL);
	p = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*p == ch)
			return (p);
		++p;
	}
	return (NULL);
}

void	dynarray_destroy(t_gnl_buffer *arr)
{
	if (!arr)
		return ;
	if (arr->data)
		free(arr->data);
	free(arr);
}

int	dynarray_append(t_gnl_buffer *arr, const void *data, size_t len)
{
	char	*new_data;
	size_t	new_capacity;
	size_t	i;

	if (!arr || !data || len == 0)
		return (0);
	if (arr->size + len > arr->capacity)
	{
		new_capacity = arr->capacity << 1;
		if (arr->size + len > new_capacity)
			new_capacity = arr->size + len;
		new_data = (char *)malloc(new_capacity);
		if (!new_data)
			return (0);
		i = -1;
		while (++i < arr->size)
			new_data[i] = arr->data[i];
		free(arr->data);
		arr->data = new_data;
		arr->capacity = new_capacity;
	}
	i = 0;
	while (i < len)
		arr->data[arr->size++] = ((const char *)data)[i++];
	return (1);
}

t_gnl_buffer	*dynarray_create(size_t initial_capacity)
{
	t_gnl_buffer	*arr;

	arr = (t_gnl_buffer *)malloc(sizeof(t_gnl_buffer));
	if (!arr)
		return (NULL);
	arr->data = (char *)malloc(initial_capacity);
	if (!arr->data)
		return (free(arr), NULL);
	arr->size = 0;
	arr->capacity = initial_capacity;
	return (arr);
}

t_gnl_node	*gnl_find_or_create_node(t_gnl_node **lst, int fd)
{
	t_gnl_node	*temp;
	t_gnl_node	*new;

	if (!lst)
		return (NULL);
	temp = *lst;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	new = (t_gnl_node *)malloc(sizeof(t_gnl_node));
	if (!new)
		return (NULL);
	new->buffer = dynarray_create(BUFFER_SIZE << 1);
	if (!new->buffer)
		return (free(new), NULL);
	new->fd = fd;
	new->next = *lst;
	*lst = new;
	return (new);
}
