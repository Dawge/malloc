/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:25:23 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/15 12:01:34 by rostroh          ###   ########.fr       */
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
	//ft_strhexout("new ptr = ", (uint64_t)new_ptr);
	res = *new_ptr;
	//ft_strhexout("Res = ", res);
//	ft_putstr("ca crash ici ?\n");
	if ((res & TINY_MASK) == TINY_MASK)
		return (TINY);
	if ((res & SMALL_MASK) == SMALL_MASK)
		return (SMALL);
	return (LARGE);
}

static void		*find_ptr(void *pool, void *to_find, int type)
{
	void		*ptr;
	uint16_t	size;
	//uint8_t		*next_ptr;
	//uint8_t		*nextnext;

	ptr = pool + g_malloc.hdrsz[type];
	size = (*((uint16_t *)ptr) ^ g_malloc.mask[type]) & IGNORE_FIRST;
	/*ft_strhexout("ptr = ", (uint64_t)ptr + g_malloc.mtdata[type]);
	ft_strhexout("On cherche : ", (uint64_t)to_find);
	ft_strhexout("ptr size = ", size);*/
	while (size != 0)
	{
		if ((uint64_t)(ptr + g_malloc.mtdata[type]) == (uint64_t)to_find)
			return (to_find);
			//return (free_zone(pool, ptr, type));
		ptr += size + g_malloc.mtdata[type];
		size = *((uint16_t *)ptr) & SIZE_MASK;
		//ft_strhexout("ptr = ", (uint64_t)ptr + g_malloc.mtdata[type]);
		//ft_strhexout("ptr size = ", size);
/*
		next_ptr = ptr + size + g_malloc.mtdata[type];
		ft_strhexout("next ptr = ", (uint64_t)next_ptr + g_malloc.mtdata[type]);
		ft_strhexout("next_ptr size = ", *((uint16_t *)next_ptr) & SIZE_MASK);

		nextnext= next_ptr + (*((uint16_t *)next_ptr) & SIZE_MASK) + g_malloc.mtdata[type];
		ft_strhexout("nextnext ptr = ", (uint64_t)nextnext + g_malloc.mtdata[type]);
		ft_strhexout("nextnext ptr size = ", *((uint16_t *)nextnext) & SIZE_MASK);*/
		//if (size != 0)
		//	size = (size ^ g_malloc.mask[type]) & IGNORE_FIRST;
	}
	return (NULL);
}

static void			*find_pool(uint8_t *to_find, int type)
{
	uint64_t	res;
	void		*old;
	void		*pool;

	old = NULL;
	pool = g_malloc.ptr[type];
	if (pool == 0x0)
		return (NULL);
	//ft_strhexout("pool = ", (uint64_t)pool);
	res = *((uint64_t*)(pool + g_malloc.bytesz[type]));
	while (res != 0)
	{
		if (find_ptr(pool, to_find, type) != NULL)
			return (old);
		/*
		if ((pool = (uint64_t*)find_ptr(pool, to_find, type)) != 0)
		{
	//		ft_putstr("eh salut\n");
			if ((uint64_t)pool == 1)
				return (type);
			if (old == NULL)
				g_malloc.ptr[type] = (uint8_t*)res;
			else
				*(old + SIZE_AREA) = (uint64_t)res;
			return (type);
		}
		else
			;//ft_strhexout("Pool addr = ", (uint64_t)pool);*/
		old = pool;
		pool = (uint8_t *)res;
		res = *((uint64_t*)(pool + g_malloc.bytesz[type]));
		//ft_strhexout("next = ", res);
	}
	if (find_ptr(pool, to_find, type) != NULL)
		return (old);
	/*if ((pool = (uint64_t*)find_ptr(pool, to_find, type)) != 0)
	{
		//ft_putstr("eh salut\n");
		if ((uint64_t)pool == 1)
			return (type);
		//ft_putstr("rochon\n");
		if (old == NULL)
			g_malloc.ptr[type] = (uint8_t*)res;
		else
			*(old + SIZE_AREA) = (uint64_t)res;
		return (type);
	}*/
	//ft_putstr("Nan, c'est chiant\n");
	return (NULL);
}

void				free(void *ptr)
{
	int		type;
	void	*pool;

	type = 0;
	while (type < NB_AREA)
	{
		if (type == LARGE)
			free_large(ptr);
		if ((pool = find_pool(ptr, type)) != NULL)
		{
		//	ft_strhexout("on free ptr : ", (uint64_t)ptr);
			free_zone(pool, ptr, type);
		}
		type++;
	}
}
/*
void				free(void *ptr)
{
	int		val;
	int		type;

	val = TINY;
	if ((uint64_t)ptr != 0)
		ft_strhexout("free ptr : ", (uint64_t)ptr);
	if ((type = get_type_mtdata(ptr)) != ERROR)
	{
		if (type != LARGE)
		{
			//ft_putstr("Chouette\n");
			val = find_pool(ptr , type);
		//	ft_strintout("C'est cool : ", val);
		}
		if (type == LARGE || val == LARGE)
		{
			//ft_strhexout("C'est un large : ", val);
			if (free_large(ptr) == 0)
				;//ft_putstr("fechie\n");
		}
	}
	if ((uint64_t)ptr != 0)
		ft_putstr("fin\n\n");
}*/
