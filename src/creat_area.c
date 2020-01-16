/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:28 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 13:54:26 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t		nb_page(size_t size, int type)
{
	if (type == LARGE)
		return (size / g_malloc.pagesz + 1);
	else
		return (g_malloc.maxsz[type] / g_malloc.pagesz + 1);
}

static void			*creat_header(void *ptr, size_t size, int type)
{
	uint16_t	res;

	if (type == LARGE)
	{
		*((uint64_t*)ptr) += size;
		return (ptr);
	}
	*((uint32_t*)ptr) += size + HEADER_SIZE;
	*((uint16_t*)(ptr + HEADER_SIZE)) = size | g_malloc.mask[type];
	res = *((uint16_t*)(ptr + HEADER_SIZE));
	return (ptr);
}

void				*creat_area(size_t size, int type)
{
	void		*ptr;
	int			size_alloc;

	size_alloc = nb_page(size, type) * g_malloc.pagesz;
	ptr = mmap(0, size_alloc, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, \
			-1, 0);
	ft_bzero(ptr, size_alloc);
	if ((VERBOSE & 0x01) == 0x01)
	{
		ft_strhexout("Creat new area : ", (uint64_t)ptr);
		ft_strhexout("with a size of : ", size_alloc);
		ft_strintout("Page before : ", g_malloc.nb_page);
		g_malloc.nb_page += nb_page(size, type);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
		ft_putchar('\n');
	}
	return (creat_header(ptr, size, type));
}
