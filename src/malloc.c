/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:11:17 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/08 22:39:19 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					g_init = 0;

static void			init_global(void)
{
	g_malloc.ptr[TINY] = NULL;
	g_malloc.ptr[SMALL] = NULL;
	g_malloc.ptr[LARGE] = NULL;
	g_malloc.hdrsz[TINY] = HEADER_SIZE;
	g_malloc.hdrsz[SMALL] = HEADER_SIZE;
	g_malloc.hdrsz[LARGE] = HEADER_LARGE;
	g_malloc.mtdata[TINY] = META_DATA;
	g_malloc.mtdata[SMALL] = META_DATA;
	g_malloc.mtdata[LARGE] = META_LARGE;
	g_malloc.bytesz[TINY] = SIZE_AREA;
	g_malloc.bytesz[SMALL] = SIZE_AREA;
	g_malloc.bytesz[LARGE] = SIZE_LARGE;
	g_malloc.maxsz[TINY] = (TINY_SIZE + META_DATA) * 100 + HEADER_SIZE;
	g_malloc.maxsz[SMALL] = (SMALL_SIZE + META_DATA) * 100 + HEADER_SIZE;
	g_malloc.mask[TINY] = TINY_MASK;
	g_malloc.mask[SMALL] = SMALL_MASK;
	g_malloc.nb_page = 0;
	g_malloc.pagesz = getpagesize();
}

static void			align(size_t *size)
{
	size_t		val;

	val = 0;
	while (val < *size)
		val += ALIGN_SIZE;
	*size = val;
	if (*size == 0)
		*size = ALIGN_SIZE;
}

int					get_type(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size <= SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

void				*malloc(size_t size)
{
	void		*ptr;

//	if (size == 0)
//		return (NULL);
	ft_strhexout("New malloc : ", (uint64_t)size);
	if (g_init == 0)
	{
		init_global();
		g_init = 1;
	}
	align(&size);
	ft_strhexout("Allign size : ", (uint64_t)size);
	ptr = handle(size, get_type(size));
	ft_strhexout("RETURN = ", (uint64_t)ptr);
	if (VERBOSE == 1)
		ft_printaddr(ptr, get_type(size));
	ft_putchar('\n');
	return (ptr);
}
