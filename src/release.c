/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/13 21:01:53 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_for_release(void *pool, int type)
{
	int			size_area;
	uint16_t	dbug;
	uint8_t		*ptr;
	uint16_t	size;

	//ft_strhexout("\nTry release pool : ", (uint64_t)pool);
	//ft_strhexout("RELEASE INC : ", (uint64_t)pool);
	ptr = pool + g_malloc.hdrsz[type];
	size = *((uint16_t *)ptr);// ^ g_malloc.mask[type]) & IGNORE_FIRST;
	//ft_strhexout("ptr = ", (uint64_t)ptr);
	//ft_strhexout("size = ", size);
	//ft_strhexout("mask = ", size & FREE_MASK);
	while (size != 0)
	{
		/*ft_strhexout("ptr = ", (uint64_t)ptr);
		ft_strhexout("size = ", size);
		ft_strhexout("mask = ", size & FREE_MASK);*/
		if ((dbug = (size & FREE_MASK)) != FREE_MASK)
		{
		//	ft_putstr("leave\n");
			return (0);
		}
		//if (size != 0)
		//	size = (size ^ g_malloc.hdrsz[type]) & IGNORE_FIRST;
		ptr += (size & SIZE_MASK) + g_malloc.mtdata[type];
		size = *((uint16_t*)ptr);
		//ft_strhexout("ptr = ", (uint64_t)ptr);
		//ft_strhexout("size = ", size);
		//ft_strhexout("mask = ", size & FREE_MASK);
	}
	/*if (size != 0 && (size & FREE_MASK) != FREE_MASK)
	{
		ft_putstr("C2\n");
		return (0);
	}*/
	size_area = (g_malloc.maxsz[type] / g_malloc.pagesz + 1) * g_malloc.pagesz;
	ft_bzero(pool, size_area);
	if (munmap(pool, size_area) == -1)
		;//ft_putstr("An error occured while releasing memory\n");
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

uint64_t		free_zone(void *pool, void *to_free, int type)
{
	uint16_t	size;
	uint64_t	next_pool;

	if ((*((uint16_t *)to_free) & FREE_MASK) == FREE_MASK)
		return (1);
	size = *((uint16_t *)to_free) & SIZE_MASK;
	//ft_strhexout("Wanna free addr : ", (uint64_t)to_free);
	//ft_strhexout("avec une size de : ", size);
	next_pool = *((uint64_t *)(pool + SIZE_AREA));
	*((uint16_t*)(to_free)) |= FREE_MASK;
	if (check_for_release(pool, type) == 0)
	{
		size = *((uint16_t *)to_free) & SIZE_MASK;
		//ft_strhexout("avec apres une size de : ", size);
		return (1);
	}
	//ft_putstr("Zooooooooooooo\n");
	//ft_strhexout("return free zone : ", (uint64_t)pool);
	return ((uint64_t)pool);
}
