/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/20 15:58:14 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_for_release(void *pool, int type)
{
	uint8_t		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = (*((uint16_t *)ptr) ^ g_malloc.mask[type]) & IGNORE_FIRST;
	while (size != 0)
	{
		ptr += size + g_malloc.mtdata[type];
		size = *((uint16_t*)ptr);
		if ((size & FREE_MASK) != FREE_MASK)
			return (1);
		if (size != 0)
			size = (size ^ g_malloc.hdrsz[type]) & IGNORE_FIRST;
	}
	if ((size & FREE_MASK) != FREE_MASK)
		return (1);
	munmap(pool, g_malloc.maxsz[type]);
	if (VERBOSE == 1)
	{
		g_malloc.nb_page -= (g_malloc.maxsz[type] / g_malloc.pagesz + 1);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
	}
	return (0);
}

uint64_t		free_zone(void *pool, void *to_free, int type)
{
	uint16_t	size;
	uint64_t	next_pool;

	ft_putstr("\n\n ON FREE QQCHOSE \n\n");
	if ((*((uint16_t *)to_free) & FREE_MASK) == FREE_MASK)
	{
		ft_putstr("Already freed\n");
		return (1);
	}
	size = *((uint16_t *)to_free) ^ g_malloc.mask[type];
	next_pool = *((uint64_t *)(pool + SIZE_AREA));
	*((uint16_t*)(to_free)) |= FREE_MASK;
	ft_bzero(to_free + 2, size);
	if (check_for_release(pool, type) == 0)
		return (next_pool);
	return (1);
}
