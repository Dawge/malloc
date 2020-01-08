/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:25:23 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/08 17:37:30 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int			get_type(uint8_t *ptr)
{
	uint16_t	res;
	uint16_t	*new_ptr;
	
	ft_strhexout("Get type ptr addr : ", (uint64_t)ptr);
	if ((uint64_t)ptr < META_DATA || (uint64_t)ptr > BIG_ADDR)
		return (ERROR);
	ft_strhexout("new addr : ", (uint64_t)(ptr - META_DATA));
	new_ptr = (uint16_t *)(ptr - META_DATA);
	ft_putstr("alive\n");
	//res = *((uint16_t *)(ptr - META_DATA));
	res = *new_ptr;
	//ft_strhexout("--> res = ", res);
	ft_putstr("debug\n");
	if ((res & TINY_MASK) == TINY_MASK)
		return (TINY);
	if ((res & SMALL_MASK) == SMALL_MASK)
		return (SMALL);
	ft_strhexout("Addr size = ", (uint64_t)(ptr - SIZE_LARGE));
	return (LARGE);
}

static uint64_t		find_ptr(void *pool, void *to_find, int type)
{
	void		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = (*((uint16_t *)ptr) ^ g_malloc.mask[type]) & IGNORE_FIRST;
//	ft_strhexout("Avant size = ", size);
	while (size != 0)
	{
//		ft_strhexout("On check : ", (uint64_t)(ptr + g_malloc.mtdata[type]));
//		ft_strhexout("Pour     : ", (uint64_t)to_find);
		if ((uint64_t)(ptr + g_malloc.mtdata[type]) == (uint64_t)to_find)
			return (free_zone(pool, ptr, type));
		ptr += size + g_malloc.mtdata[type];
		size = *((uint16_t *)ptr);
		if (size != 0)
			size = (size ^ g_malloc.mask[type]) & IGNORE_FIRST;
//		ft_strhexout("After : ", (uint64_t)ptr);
//		ft_strhexout("Size  : ", size);
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
	res = *((uint64_t*)(pool + SIZE_AREA));
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
		res = *((uint64_t*)(pool + SIZE_AREA));
	}
	if (find_ptr(pool, to_find, type) == 1)
		return (type);
	return (LARGE);
}

void				free(void *ptr)
{
	int		val;
	int		type;

	ft_strhexout("Ici pour free : ", (uint64_t)ptr);
	if ((type = get_type(ptr)) != ERROR)
	{
		if (type != LARGE)
		{
			ft_putstr("Ceci est bien\n");
			val = find_pool(ptr , type);
		}
		if (type == LARGE || val == LARGE)
			ft_putstr("Large detected\n");//free_large(ptr);
		ft_putchar('\n');
	}
	else
		ft_putstr("ERROR\n\n\n");
}
