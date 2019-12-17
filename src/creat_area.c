/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 21:58:45 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t		size_alloc(size_t size, int type)
{
	if (type == TINY)
		return (TINY_SIZE * 100 / g_malloc.pagesz);
	else if (type == SMALL)
		return (SMALL_SIZE * 100 / g_malloc.pagesz);
	else
		return (size / g_malloc.pagesz + 1);
}

static void			*creat_header(void *ptr, size_t size, int type)
{
	if (type == LARGE)
	{
		*((uint64_t*)ptr) += size;
		return (ptr);
	}
	*((uint32_t*)ptr) += size + HEADER_SIZE;
	*((uint16_t*)(ptr + HEADER_SIZE)) = size;
	return (ptr);
}

void				*creat_area(size_t size, int type)
{
	void		*ptr;

	ptr = mmap(0, size_alloc(size, type), PROT_READ | PROT_WRITE, MAP_ANON | \
			MAP_PRIVATE, -1, 0);
	ft_bzero(ptr, size_alloc(size, type));
	if (VERBOSE == 1)
	{
		g_malloc.nb_page += size_alloc(size, type);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
	}
	return (creat_header(ptr, size, type));
}
