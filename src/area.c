/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:19 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/13 21:02:13 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** if full == 1, area is full.
** Otherwise, enought space for add malloc
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
	res = *((uint64_t*)(ptr + g_malloc.bytesz[type]));//SIZE_AREA));
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

	res = *((uint16_t*)(ptr + g_malloc.hdrsz[type])) & SIZE_MASK;//^ g_malloc.mask[type])  
		//  & IGNORE_FIRST;
	ptr += g_malloc.hdrsz[type];
	while (res != 0)
	{
		ptr += res + g_malloc.mtdata[type];
		res = *((uint16_t*)ptr);
		if ((res & FREE_MASK) == FREE_MASK && size <= (res & SIZE_MASK))
		{
			*(uint16_t*)(ptr) ^= FREE_MASK;
			*freed = 1;/*
			ft_putstr("Dobby est libre !\n");
			ft_strhexout("Freed zone at : ", (uint64_t)ptr);
			ft_strhexout("size = ", res);*/
			return (ptr);
		}
		if (res != 0)
			res = (res ^ g_malloc.mask[type]) & IGNORE_FIRST;
	}
	return (ptr + res);
}

void				*handle(size_t size, int t)
{
	int			full;
	int			freed;
	uint8_t		*ptr;
	uint64_t	res;

	full = 0;
	freed = 0;
	if (g_malloc.ptr[t] == NULL)
	{
		g_malloc.ptr[t] = creat_area(size, t);
	//	ft_strhexout("Pool : ", (uint64_t)g_malloc.ptr[t]);
		return (g_malloc.ptr[t] + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
	ptr = go_last_area(t, size, &full);
	//ft_strhexout("Pool : ", (uint64_t)ptr);
	if (full == 0)
	{
		*((uint32_t*)(ptr)) += (uint32_t)size + META_DATA;
		ptr = pars_block(ptr, t, size, &freed);
		if (freed == 0)
			*((uint16_t*)(ptr)) = size | g_malloc.mask[t];
		else
			;//ft_strhexout("Cheh : ", (*((uint16_t*)(ptr)) & SIZE_MASK));
		return (ptr + g_malloc.mtdata[t]);
	}
	else
	{
		res = (uint64_t)creat_area(size, t);
		*(uint64_t*)(ptr + g_malloc.bytesz[t]) = res;
		ptr = (uint8_t*)res;
		return (ptr + g_malloc.hdrsz[t] + g_malloc.mtdata[t]);
	}
}
