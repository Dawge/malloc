/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/15 11:56:45 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_for_release(void *pool, int type)
{
	int			size_area;
	uint16_t	dbug;
	uint8_t		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = *((uint16_t *)ptr);// ^ g_malloc.mask[type]) & IGNORE_FIRST;
	while (size != 0)
	{
		if ((dbug = (size & FREE_MASK)) != FREE_MASK)
			return (0);
		ptr += (size & SIZE_MASK) + g_malloc.mtdata[type];
		size = *((uint16_t*)ptr);
	}
	if (size != 0 && (size & FREE_MASK) != FREE_MASK)
		return (0);
	size_area = (g_malloc.maxsz[type] / g_malloc.pagesz + 1) * g_malloc.pagesz;
	ft_bzero(pool, size_area);
	if (munmap(pool, size_area) == -1)
		return (0);
	if (VERBOSE == 1)
	{
		ft_strhexout("Release addr : ", (uint64_t)pool);
		ft_strhexout("with a size of : ", size_area);
		g_malloc.nb_page -= (g_malloc.maxsz[type] / g_malloc.pagesz + 1);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
		ft_putchar('\n');
	}
	return (1);
}

uint64_t		free_zone(uint8_t *old_pool, void *to_free, int type)
{
	uint8_t		*pool;
	//uint16_t	size;
	uint64_t	next_pool;

	if (old_pool == NULL)
		pool = g_malloc.ptr[type];
	else
		pool = (uint8_t*)(*((uint64_t*)(old_pool + SIZE_AREA)));
	if ((*((uint16_t *)to_free) & FREE_MASK) == FREE_MASK)
		return (1);
	//size = *((uint16_t *)to_free) & SIZE_MASK;
	next_pool = *((uint64_t *)(pool + SIZE_AREA));
	*((uint16_t*)(to_free)) |= FREE_MASK;
	if (check_for_release(pool, type) == 0)
	{
		//size = *((uint16_t *)to_free) & SIZE_MASK;
		return (1);
	}
	if (old_pool == NULL)
		g_malloc.ptr[type] = (uint8_t*)next_pool;
	else
		*((uint64_t*)(old_pool + SIZE_AREA)) = next_pool;
	return ((uint64_t)pool);
}
