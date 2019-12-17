/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 18:42:59 by rostroh          ###   ########.fr       */
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

void				*creat_area(size_t size, int type)
{
	void		*ptr;

	ptr = mmap(0, size_alloc(size, type), PROT_READ | PROT_WRITE, MAP_ANON | \
			MAP_PRIVATE, -1, 0);
	if (VERBOSE == 1)
	{
		g_malloc.nb_page += size_alloc(size, type);
		ft_strintout("Page reclaims : ", g_malloc.nb_page);
	}
	return (ptr);
}
