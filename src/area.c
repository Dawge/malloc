/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:19 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 14:38:11 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	res = *((uint64_t*)(ptr + g_malloc.bytesz[type]));
	while (res != 0)
	{
		if ((*full = is_full(ptr, size, type)) == 0)
			return (ptr);
		ptr = (uint8_t*)res;
		res = *((uint64_t*)(ptr + g_malloc.bytesz[type]));
	}
	*full = is_full(ptr, size, type);
	return (ptr);
}

static uint8_t		*pars_block(uint8_t *ptr, int type, size_t size, int *freed)
{
	uint16_t	res;

	res = *((uint16_t*)(ptr + g_malloc.hdrsz[type])) & SIZE_MASK;
	ptr += g_malloc.hdrsz[type];
	while (res != 0)
	{
		ptr += res + g_malloc.mtdata[type];
		res = *((uint16_t*)ptr);
		if ((res & FREE_MASK) == FREE_MASK && size <= (res & SIZE_MASK))
		{
			*(uint16_t*)(ptr) ^= FREE_MASK;
			*freed = 1;
			return (ptr);
		}
		if (res != 0)
			res = (res ^ g_malloc.mask[type]) & IGNORE_FIRST;
	}
	return (ptr + res);
}

static uint8_t		*can_be_filled(uint8_t *ptr, int size, int type)
{
	int			freed;
	uint8_t		*cpy;

	freed = 0;
	cpy = ptr;
	ptr = pars_block(ptr, type, size, &freed);
	if (freed == 0)
	{
		*((uint16_t*)(ptr)) = size | g_malloc.mask[type];
		*((uint32_t*)(cpy)) += (uint32_t)size + META_DATA;
	}
	return (ptr + g_malloc.mtdata[type]);
}

void				*handle(size_t size, int t)
{
	int			full;
	uint8_t		*ptr;
	uint64_t	res;

	full = 0;
	if (g_malloc.ptr[t] == NULL)
	{
		g_malloc.ptr[t] = creat_area(size, t);
		return (g_malloc.ptr[t] + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
	ptr = go_last_area(t, size, &full);
	if (full == 0)
		return (can_be_filled(ptr, size, t));
	else
	{
		res = (uint64_t)creat_area(size, t);
		*(uint64_t*)(ptr + g_malloc.bytesz[t]) = res;
		ptr = (uint8_t*)res;
		return (ptr + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
}
