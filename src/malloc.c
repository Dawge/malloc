/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:11:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 22:05:48 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			init_global(void)
{
	g_malloc.ptr_tiny = NULL;
	g_malloc.ptr_small = NULL;
	g_malloc.ptr_large = NULL;
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
