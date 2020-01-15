/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/15 15:42:42 by rostroh          ###   ########.fr       */
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

uint64_t		free_zone(uint8_t *pool, uint8_t *old, void *to_free, int type)
{
//	uint8_t		*pool;
	uint16_t	size;
	uint64_t	next_pool;

//	if (old_pool == NULL)
//		pool = g_malloc.ptr[type];
//	else
//		pool = (uint8_t*)(*((uint64_t*)(old_pool + SIZE_AREA)));
	//ft_strhexout("dams free zone pool = ", (uint64_t)pool);
	if ((*((uint16_t *)to_free) & FREE_MASK) == FREE_MASK)
		return (1);
	//ft_strhexout("on veux free addr : ", (uint64_t)to_free);
	size = *((uint16_t *)to_free) & SIZE_MASK;
	//ft_strhexout("Size = ", size);
	next_pool = *((uint64_t *)(pool + SIZE_AREA));
	*((uint16_t*)(to_free)) |= FREE_MASK;
	//ft_strhexout("Size apres= ", size);
	size = *((uint16_t *)to_free);
	if (check_for_release(pool, type) == 0)
	{
		return (1);
	}
	if (old == NULL)
	{
		g_malloc.ptr[type] = (uint8_t*)next_pool;
	//	ft_strhexout("New ptr = ", (uint64_t)g_malloc.ptr[type]);
	}
	else
	{
	//	ft_strhexout("old_pool next = ", *((uint64_t*)(old + SIZE_AREA)));
		*((uint64_t*)(old + SIZE_AREA)) = next_pool;
	//	ft_strhexout("now = ", *((uint64_t*)(old + SIZE_AREA)));
	}
	return ((uint64_t)pool);
}
