/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 14:50:27 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		release_verbose(void *pool, int size_pool, int type)
{
	{
		ft_strhexout("Release addr : ", (uint64_t)pool);
		ft_strhexout("with a size of : ", size_pool);
		g_malloc.nb_page -= (g_malloc.maxsz[type] / g_malloc.pagesz + 1);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
		ft_putchar('\n');
	}
}

int				check_for_release(void *pool, int type)
{
	int			size_pool;
	uint8_t		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = *((uint16_t *)ptr);
	while (size != 0)
	{
		if ((size & FREE_MASK) != FREE_MASK)
			return (0);
		ptr += (size & SIZE_MASK) + g_malloc.mtdata[type];
		size = *((uint16_t*)ptr);
	}
	if (size != 0 && (size & FREE_MASK) != FREE_MASK)
		return (0);
	size_pool = (g_malloc.maxsz[type] / g_malloc.pagesz + 1) * g_malloc.pagesz;
	ft_bzero(pool, size_pool);
	if (munmap(pool, size_pool) == -1)
		return (0);
	if ((VERBOSE & 0x01) == 0x01)
		release_verbose(pool, size_pool, type);
	return (1);
}

uint64_t		free_zone(uint8_t *pool, uint8_t *old, void *to_free, int type)
{
	uint16_t	size;
	uint64_t	next_pool;

	if ((*((uint16_t *)to_free) & FREE_MASK) == FREE_MASK)
		return (1);
	size = *((uint16_t *)to_free) & SIZE_MASK;
	next_pool = *((uint64_t *)(pool + SIZE_AREA));
	*((uint16_t*)(to_free)) |= FREE_MASK;
	size = *((uint16_t *)to_free);
	if (check_for_release(pool, type) == 0)
		return (1);
	if (old == NULL)
		g_malloc.ptr[type] = (uint8_t*)next_pool;
	else
		*((uint64_t*)(old + SIZE_AREA)) = next_pool;
	return ((uint64_t)pool);
}
