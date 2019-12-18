/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/18 21:03:35 by rostroh          ###   ########.fr       */
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
	if (type == LARGE)
	{
		*((uint64_t*)ptr) += size;
		return (ptr);
	}
	*((uint32_t*)ptr) += size + HEADER_SIZE;
	ft_strhexout("header value : ", *((uint32_t*)ptr));
	*((uint16_t*)(ptr + HEADER_SIZE)) = size | g_malloc.mask[type];
	ft_strhexout("meta data : ", *((uint16_t*)(ptr + HEADER_SIZE)) ^ g_malloc.mask[type]);
	return (ptr);
}

void				*creat_area(size_t size, int type)
{
	void		*ptr;
	int			size_alloc;

	size_alloc = nb_page(size, type) * g_malloc.pagesz;
	ptr = mmap(0, size_alloc, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, \
			-1, 0);
	ft_strhexout("map addr : ", (uint64_t)ptr);
	ft_bzero(ptr, size_alloc);
	ft_strhexout("map size : ", size_alloc);
	if (VERBOSE == 1)
	{
		g_malloc.nb_page += nb_page(size, type);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
	}
	return (creat_header(ptr, size, type));
}
