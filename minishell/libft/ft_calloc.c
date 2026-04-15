/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:58:14 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 17:12:47 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man calloc - allocate and free dynamic memory
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <stdlib.h>
 *
 *      void *calloc(size_t nmemb, size_t size);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The calloc() function allocates memory for an array of nmemb elements 
 * 	of size bytes each and returns a pointer to the allocated memory. 
 * 	The memory is set to zero. If nmemb or size is 0, then calloc() 
 * 	returns either NULL, or a unique pointer value that can later be 
 * 	successfully passed to free(). If the multiplication of nmemb and 
 * 	size would result in integer overflow, then calloc() returns an 
 * 	error. By contrast, an integer overflow would not be detected in the
 * 	following call to malloc(), with the result that an incorrectly sized 
 * 	block of memory would be allocated:
 * 
 *  		malloc(nmemb * size);
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      The calloc() function return a pointer to the allocated memory, 
 * 	which is suitably aligned for any built-in type. On error, these 
 * 	functions return NULL. NULL may also be returned by a successful call 
 * 	to calloc() with nmemb or size equal to zero.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total_size;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	result = malloc(total_size);
	if (result != NULL)
		ft_bzero(result, total_size);
	return (result);
}
