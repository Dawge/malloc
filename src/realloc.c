/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:54:18 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 15:16:24 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		check_size(uint8_t *ptr, size_t size, int type, int ptr_type)
{
	if (size <= (*(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]) & SIZE_MASK))
	{
		if (ptr_type == type)
			return (1);
	}
	return (0);
}

static void		cpy_data(uint8_t *dst, uint8_t *src, int dst_type, int src_type)
{
	int			i;
	uint16_t	dstsz;
	uint16_t	srcsz;

	i = 0;
	dstsz = *(uint16_t*)(dst - g_malloc.mtdata[dst_type]) & SIZE_MASK;
	srcsz = *(uint16_t*)(src - g_malloc.mtdata[src_type]) & SIZE_MASK;
	while (i < srcsz)
	{
		dst[i] = src[i];
		i++;
		if (i == dstsz)
			break ;
	}
}

static void		*handle_realloc(void *ptr, size_t size, int type, int ptr_type)
{
	uint8_t		*new_ptr;

	if (type == LARGE)
	{
		new_ptr = malloc(size);
		cpy_data(new_ptr, ptr, type, ptr_type);
		free(ptr);
		return (new_ptr);
	}
	if (check_size(ptr, size, type, ptr_type) == 1)
		return (ptr);
	else if (type == ptr_type && check_enlarge(ptr, size, type, ptr_type) == 1)
		return (ptr);
	else
	{
		new_ptr = malloc(size);
		cpy_data(new_ptr, ptr, type, ptr_type);
		free(ptr);
		return (new_ptr);
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	int			type;
	int			ptr_type;
	uint8_t		*old;

	type = 0;
	ptr_type = 0;
	if (ptr == NULL)
		return (malloc(size));
	while (ptr_type < NB_AREA)
	{
		if (find_pool(ptr, &old, ptr_type) != NULL)
			break ;
		ptr_type++;
	}
	if (ptr_type == NB_AREA)
		return (NULL);
	type = get_type(size);
	return (handle_realloc(ptr, size, type, ptr_type));
}
