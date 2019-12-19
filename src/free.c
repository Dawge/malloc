/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:25:23 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/19 17:46:45 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		get_type(void *ptr)
{
	int			res;

	if ((uint64_t)ptr < META_DATA)
		return (ERROR);
	res = *((uint16_t *)(ptr - META_DATA));
	if ((res & TINY_MASK) == TINY_MASK)
		return (TINY);
	if ((res & SMALL_MASK) == SMALL_MASK)
		return (SMALL);
	return (LARGE);
}

static int		find_ptr(void *pool, void *to_find, int type)
{
	void		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = *((uint16_t *)ptr) ^ g_malloc.mask[type] ^ FREE_MASK;
	while (size != 0)
	{
		if (ptr + g_malloc.mtdata[type] == to_find)
			return (free_zone(pool, ptr, type));
		ptr += size + g_malloc.mtdata[type];
		size = *((uint16_t*)ptr);
		if (size != 0)
			size ^= g_malloc.mask[type] ^ FREE_MASK;
	}
	return (0);
}

static int		find_pool(void *to_find, int type)
{
	uint64_t	res;
	void		*pool;
	void		*looking;

	pool = g_malloc.ptr[type];
	res = *((uint64_t*)(pool + SIZE_AREA));
	while (res != 0)
	{
		if (find_ptr(pool, to_find, type) == 1)
		{
			return (type);
		}
		pool = (uint8_t *)res;
		res = *((uint64_t*)(pool + SIZE_AREA));
	}
	if (find_ptr(pool, to_find, type) == 1)
	{
		return (type);
	}
	return (LARGE);
}

void			free(void *ptr)
{
	int		val;
	int		type;

	if ((type = get_type(ptr)) != ERROR)
	{
		if (type != LARGE)
			val = find_pool(ptr - 2, type);
		if (type == LARGE || val == LARGE)
			free_large(ptr);
	}
}
