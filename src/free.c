/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:25:23 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/10 18:59:43 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					get_type_mtdata(uint8_t *ptr)
{
	uint16_t	res;
	uint16_t	*new_ptr;

	if ((uint64_t)ptr < META_DATA || (uint64_t)ptr > BIG_ADDR)
		return (ERROR);
	new_ptr = (uint16_t *)(ptr - META_DATA);
	res = *new_ptr;
	if ((res & TINY_MASK) == TINY_MASK)
	{
		return (TINY);
	}
	if ((res & SMALL_MASK) == SMALL_MASK)
		return (SMALL);
	return (LARGE);
}

static uint64_t		find_ptr(void *pool, void *to_find, int type)
{
	void		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = (*((uint16_t *)ptr) ^ g_malloc.mask[type]) & IGNORE_FIRST;
	while (size != 0)
	{
		if ((uint64_t)(ptr + g_malloc.mtdata[type]) == (uint64_t)to_find)
			return (free_zone(pool, ptr, type));
		ptr += size + g_malloc.mtdata[type];
		size = *((uint16_t *)ptr);
		if (size != 0)
			size = (size ^ g_malloc.mask[type]) & IGNORE_FIRST;
	}
	return (0);
}

static int			find_pool(uint8_t *to_find, int type)
{
	uint64_t	res;
	uint64_t	*old;
	void		*pool;

	old = NULL;
	pool = g_malloc.ptr[type];
	res = *((uint64_t*)(pool + g_malloc.bytesz[type]));
	while (res != 0)
	{
		if ((pool = (uint64_t*)find_ptr(pool, to_find, type)) != 0)
		{
			if ((uint64_t)pool == 1)
				return (type);
			if (old == NULL)
				g_malloc.ptr[type] = (uint8_t*)res;
			else
				*(old + SIZE_AREA) = (uint64_t)pool;
			return (type);
		}
		old = pool;
		pool = (uint8_t *)res;
		res = *((uint64_t*)(pool + g_malloc.bytesz[type]));
	}
	if (find_ptr(pool, to_find, type) == 1)
		return (type);
	return (LARGE);
}

static int			free_large(uint8_t *ptr)
{
	uint8_t		*res;
	uint8_t		*old;
	uint64_t	next_addr;

	res = g_malloc.ptr[LARGE];
	if (res + HEADER_LARGE == ptr)
	{
		g_malloc.ptr[LARGE] = (void*)(*(uint64_t*)(res + SIZE_LARGE));
		munmap(res, (uint64_t)(*res) / 16 + 1);
		return (1);
	}
	next_addr = *(uint64_t*)(res + SIZE_LARGE);
	while (next_addr != 0)
	{
		old = res;
		res = (uint8_t*)next_addr;
		next_addr = *(uint64_t*)(res + SIZE_LARGE);
		if (res + HEADER_LARGE == ptr)
		{
			*(uint64_t*)(old + SIZE_LARGE) = next_addr;
			munmap(res, (uint64_t)(*res) / 16 + 1);
			return (1);
		}
	}
	return (0);
}

void				free(void *ptr)
{
	int		val;
	int		type;

	ft_strhexout("Ici pour free : ", (uint64_t)ptr);
	if ((type = get_type_mtdata(ptr)) != ERROR)
	{
		if (type != LARGE)
		{
			val = find_pool(ptr , type);
		}
		if (type == LARGE || val == LARGE)
		{
			if (free_large(ptr) == 0)
				ft_putstr("fechie\n");
			else
				ft_putstr("C'est franchement cool\n");
		}
		ft_putchar('\n');
	}
	else
		ft_putstr("ERROR\n\n\n");
}
