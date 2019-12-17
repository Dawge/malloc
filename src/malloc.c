/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:11:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 22:35:38 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	g_malloc.maxsz[TINY] = (TINY_SIZE + META_DATA) * 100 + HEADER_SIZE;
	g_malloc.maxsz[SMALL] = (SMALL_SIZE + META_DATA) * 100 + HEADER_SIZE;
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
}

void				*malloc(size_t size)
{
	init_global();
	align(&size);
	if (size <= TINY_SIZE)
		return (handle_tiny(size));
	else if (size <= SMALL_SIZE)
		return (handle_small(size));
	else
		return (handle_large(size));
	return (NULL);
}
