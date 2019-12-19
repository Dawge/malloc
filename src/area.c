/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:19 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/19 18:05:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** if full == 1, area is full. Otherwise, enought space for add malloc
*/
static int			is_full(uint8_t *ptr, size_t size, int type)
{
	uint32_t		res;

	if (type == LARGE)
		return (1);
	res = *((uint32_t*)(ptr));
	ft_strhexout("SIZE IN AREA : ", (uint64_t)res);
	ft_strhexout("MAX SIZE AREA : ", g_malloc.maxsz[type]);
	if (res + size >= g_malloc.maxsz[type])
		return (1);
	return (0);
}

static uint8_t		*go_last_area(int type, size_t size, int *full)
{
	uint8_t		*ptr;
	uint64_t	res;

	ptr = g_malloc.ptr[type];
	ft_strhexout("First addr = ", (uint64_t)ptr);
	res = *((uint64_t*)(ptr + SIZE_AREA));
	ft_strhexout("Next addr  = ", res);
	while (res != 0)
	{
		if ((*full = is_full(ptr, size, type)) == 0)
			return (ptr);
		ptr = (uint8_t*)res;
		res = *((uint64_t*)(ptr + SIZE_AREA));
	}
	*full = is_full(ptr, size, type);
	return (ptr);
}

static uint8_t		*pars_block(uint8_t *ptr, int type)
{
	uint16_t	res;

	res = (*((uint16_t*)(ptr + g_malloc.hdrsz[type])) ^ g_malloc.mask[type])  \
		  & IGNORE_FIRST;
	ptr += g_malloc.hdrsz[type];
	//ft_strhexout("res avant = ", *((uint16_t*)(ptr + g_malloc.hdrsz[type])));
	while (res != 0)
	{
		//ft_strhexout("old ptr = ", (uint64_t)ptr);
		//ft_strhexout("block size = ", (uint64_t)res);
		ptr += res + g_malloc.mtdata[type];
		res = *((uint16_t*)ptr);
		if (res != 0)
			res = (res ^ g_malloc.mask[type]) & IGNORE_FIRST;
	}
	//ft_strhexout("end ptr = ", (uint64_t)ptr);
	return (ptr + res);
}

void				*handle(size_t size, int t)
{
	int			full;
	uint8_t		*ptr;
	uint64_t	res;

	full = 0;
	if (g_malloc.ptr[t] == NULL)
	{
		ft_putstr("First area\n");
		g_malloc.ptr[t] = creat_area(size, t);
		return (g_malloc.ptr[t] + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
	ptr = go_last_area(t, size, &full);
	if (full == 0)
	{
	//	ft_putstr("appends blocks\n");
		*((uint32_t*)(ptr)) += (uint32_t)size + META_DATA;
		ptr = pars_block(ptr, t);
		ft_strhexout("ptr = ", (uint64_t)ptr);
		ft_strhexout("size = ", (uint64_t)size);
		*((uint16_t*)(ptr)) = size | g_malloc.mask[t];
		//ft_strhexout("val ptr = ", *((uint16_t*)(ptr)));
		return (ptr + g_malloc.mtdata[t]);
	}
	else
	{
		ft_putstr("creat new area\n");
		res = (uint64_t)creat_area(size, t);
		*(uint64_t*)(ptr + SIZE_AREA) = res;
		ptr = (uint8_t*)res;
		return (ptr + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
}
