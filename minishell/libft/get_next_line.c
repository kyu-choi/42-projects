/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:51:39 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Reads data from a file descriptor into a dynamic array buffer
 * @details Repeatedly reads chunks from the file until it finds a newline 
 * 			character, reaches end-of-file, or encounters an error. The read 
 * 			data is appended to the provided dynamic array buffer.
 * @param fd File descriptor to read from
 * @param buffer Pointer to a dynamic array where read data will be stored
 * @return 1 if successful (found newline or EOF with data), 0 on failure or 
 * 			EOF without data
 */
static int	read_file_to_buffer(int fd, t_gnl_buffer *buffer)
{
	char	*temp_buffer;
	ssize_t	bytes;

	temp_buffer = malloc(BUFFER_SIZE);
	if (!temp_buffer)
		return (0);
	while (1)
	{
		bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (free(temp_buffer), bytes == 0 && buffer->size > 0);
		if (!dynarray_append(buffer, temp_buffer, bytes))
			return (free(temp_buffer), 0);
		if (ft_memchr(buffer->data, '\n', buffer->size))
			return (free(temp_buffer), 1);
	}
}

/**
 * @brief Removes a node from the list based on file descriptor
 * @details This function finds and removes a node that matches the given file 
 * 			descriptor from the linked list. It properly cleans up by 
 * 			destroying the dynamic array buffer associated with the node before
 * 			freeing the node itself.
 * 
 * @param lst Pointer to the head pointer of the linked list
 * @param fd File descriptor to identify which node to remove
 * 
 * @return None
 * 
 * @note If the list pointer is NULL, the list is empty, or the node with the
 *       specified fd is not found, the function returns without making changes.
 */
static void	ft_lst_remove(t_gnl_node **lst, int fd)
{
	t_gnl_node	*temp;
	t_gnl_node	*prev;

	if (!lst || !*lst)
		return ;
	if ((*lst)->fd == fd)
	{
		temp = *lst;
		*lst = (*lst)->next;
	}
	else
	{
		prev = *lst;
		while (prev->next && prev->next->fd != fd)
			prev = prev->next;
		if (!prev->next)
			return ;
		temp = prev->next;
		prev->next = temp->next;
	}
	if (temp->buffer)
		dynarray_destroy(temp->buffer);
	free(temp);
}

/**
 * @brief Extracts a line from a dynamic array buffer
 * @details This function extracts a complete line from the buffer, including 
 * 			the newline character if present. A line is defined as all 
 * 			characters up to and including the first newline character, or the 
 * 			entire buffer if no newline is found. The extracted line is 
 * 			returned as a newly allocated string.
 *
 * @param buffer Pointer to the dynamic array containing the data to extract 
 * 					from
 * @return A newly allocated string containing the extracted line, or NULL if:
 *         - the buffer pointer is NULL
 *         - the buffer is empty
 *         - memory allocation fails
 *
 * @note The caller is responsible for freeing the returned string
 * @note This function does not modify the original buffer; use update_buffer()
 *       to remove the extracted line from the buffer
 */
static char	*extract_line(t_gnl_buffer *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!buffer || buffer->size == 0)
		return (NULL);
	i = 0;
	while (i < buffer->size && buffer->data[i] != '\n')
		++i;
	if (i < buffer->size)
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = buffer->data[j];
	if (i < buffer->size)
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/**
 * @brief Updates the buffer after a line has been read
 * @details This function updates the buffer after extracting a line by:
 *          1. Finding the first newline character in the buffer
 *          2. If there's content after the newline, creating a new buffer
 *             containing only that remaining content
 *          3. If there's no content after the newline or no newline is found,
 *             clearing the buffer entirely
 *          The original buffer is always properly destroyed and the buffer
 *          pointer is updated accordingly.
 *
 * @param buffer Pointer to the buffer pointer to update
 * @return 1 on successful update, 0 if buffer is NULL, empty, or if memory
 *         allocation fails during the update process
 *
 * @note This function is critical for maintaining the static buffer between
 *       multiple calls to get_next_line, ensuring that only unprocessed data
 *       is kept for subsequent reads
 */
static int	update_buffer(t_gnl_buffer **buffer)
{
	t_gnl_buffer	*new_buffer;
	size_t			i;

	if (!buffer || !*buffer)
		return (0);
	i = 0;
	while (i < (*buffer)->size && (*buffer)->data[i] != '\n')
		++i;
	if (i + 1 < (*buffer)->size)
	{
		new_buffer = dynarray_create((*buffer)->capacity);
		if (!new_buffer)
			return (0);
		if (!dynarray_append(new_buffer, (*buffer)->data + i + 1,
				(*buffer)->size - i - 1))
			return (dynarray_destroy(new_buffer), 0);
		dynarray_destroy(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		dynarray_destroy(*buffer);
		*buffer = NULL;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl_node	*list;
	t_gnl_node			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = gnl_find_or_create_node(&list, fd);
	if (!node)
		return (NULL);
	if (!node->buffer)
		node->buffer = dynarray_create(BUFFER_SIZE << 1);
	if (!node->buffer || !read_file_to_buffer(fd, node->buffer))
		return (ft_lst_remove(&list, fd), NULL);
	line = extract_line(node->buffer);
	if (!line)
		return (ft_lst_remove(&list, fd), NULL);
	if (!update_buffer(&node->buffer))
		return (ft_lst_remove(&list, fd), line);
	if (!node->buffer)
		ft_lst_remove(&list, fd);
	return (line);
}
