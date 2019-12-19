/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/19 20:13:28 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			check_for_release(void *pool, int type)
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
			return ;
		if (size != 0)
			size = (size ^ g_malloc.hdrsz[type]) & IGNORE_FIRST;
	}
	if ((size & FREE_MASK) != FREE_MASK)
		return ;
	//munmap
}

int				free_zone(void *pool, void *to_free, int type)
{
	uint16_t	size;

	//check if to_free is already
	size = *((uint16_t *)to_free) ^ g_malloc.mask[type];
	*((uint16_t*)(to_free)) |= FREE_MASK;
	ft_bzero(to_free + 2, size);
	check_for_release(pool, type);
	return (1);
}
