/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
uu/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:19 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 22:47:22 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


/*
**	if full == 1, area is full. Otherwise, enought space for add malloc
*/
static int			is_full(uint8_t *ptr, size_t size, int type)
{
	uint32_t		res;

	if (type == LARGE)
		return (1);
	res = *((uint32_t*)(ptr));
	if (res + size >= g_malloc.maxsz[type])
		return (1);
	return (0);
}

static uint8_t		*go_last_area(int type, size_t size, int *full)
{
	uint8_t		*ptr;
	uint64_t	res;

	ptr = g_malloc.ptr[type];
	res = *((uint64_t*)(ptr + g_malloc.hdrsz[type]));
	while (res != 0)
	{
		if ((*full = is_full(ptr, size, type)) == 0)
			return (ptr);
		ptr = (uint8_t*)res;
		res = *((uint64_t*)(ptr + g_malloc.hdrsz[type]));
	}
	*full = is_full(ptr, size, type);
	return (ptr);
}

void				*handle(size_t size, int t)
{
	int			full;
	uint8_t		*ptr;
	uint64_t	res;

	full = 0;
	if (g_malloc.ptr[t] == NULL)
		return (creat_area(size, t) + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	ptr = go_last_area(t, size, &full);
	if (full == 0)
	{
		//pars block : last block dispo + sa size
	}
	else
	{
		res = (uint64_t)creat_area(size, t);
		*(uint64_t*)(ptr + g_malloc.hdrsz[t]) = (uint64_t)res;
		ptr = (uint8_t*)res;
		return (ptr + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
}
/*
void				*handle_tiny(size_t size)
{
	int			full;
	uint8_t		*ptr;
	uint64_t	*res;

	full = 0;
	if (g_malloc.ptr_tiny == NULL)
		return (creat_area(size, TINY) + HEADER_SIZE + META_DATA);
	ptr = go_last_area(TINY, &full);
	if (full == 0)
	{
	}
	else
	{
		res = (uint64_t*)creat_area(size, TINY);
	}
	return (NULL);
}

void				*handle_small(size_t size)
{
	if (g_malloc.ptr_small == NULL)
		return (creat_area(size, SMALL));
	return (NULL);
}

void				*handle_large(size_t size)
{
	if (g_malloc.ptr_large == NULL)
		return (creat_area(size, LARGE));
	return (NULL);
}
