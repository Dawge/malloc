/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:01:42 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 15:00:04 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		verbose_large(int size)
{
	if ((VERBOSE & 0x01) == 0x01)
	{
		g_malloc.nb_page -= size;
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
	}
}

static void		free_first(uint8_t *res)
{
	uint64_t	size;

	g_malloc.ptr[LARGE] = (void*)(*(uint64_t*)(res + SIZE_LARGE));
	size = (uint64_t)(*res) / g_malloc.pagesz + 1;
	munmap(res, size * g_malloc.pagesz);
	verbose_large(size);
}

void			free_large(uint8_t *ptr)
{
	uint8_t		*res;
	uint8_t		*old;
	uint64_t	size;
	uint64_t	next_addr;

	res = g_malloc.ptr[LARGE];
	if (res == NULL)
		return ;
	if (ptr >= res && res + HEADER_LARGE == ptr)
		return (free_first(res));
	next_addr = *(uint64_t*)(res + SIZE_LARGE);
	while (next_addr != 0)
	{
		old = res;
		res = (uint8_t*)next_addr;
		next_addr = *(uint64_t*)(res + SIZE_LARGE);
		if (ptr >= res && res + HEADER_LARGE == ptr)
		{
			*(uint64_t*)(old + SIZE_LARGE) = next_addr;
			size = (uint64_t)(*res) / 16 + 1;
			munmap(res, size);
			verbose_large(size);
		}
	}
}
