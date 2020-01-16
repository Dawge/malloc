/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:25:23 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 14:30:42 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*find_ptr(void *pool, void *to_find, int type)
{
	void		*ptr;
	uint16_t	size;

	ptr = pool + g_malloc.hdrsz[type];
	size = *((uint16_t *)ptr) & SIZE_MASK;
	while (size != 0)
	{
		if ((uint64_t)(ptr + g_malloc.mtdata[type]) == (uint64_t)to_find)
			return (to_find);
		ptr += size + g_malloc.mtdata[type];
		size = *((uint16_t *)ptr) & SIZE_MASK;
	}
	if ((uint64_t)(ptr + g_malloc.mtdata[type]) == (uint64_t)to_find)
		return (to_find);
	return (NULL);
}

void				*find_pool(uint8_t *to_find, uint8_t **old, int type)
{
	uint64_t	res;
	void		*pool;

	pool = g_malloc.ptr[type];
	if (pool == 0x0)
		return (NULL);
	res = *((uint64_t*)(pool + g_malloc.bytesz[type]));
	while (res != 0)
	{
		if (type != LARGE && find_ptr(pool, to_find, type) != NULL)
			return (pool);
		if (type == LARGE && to_find == pool + HEADER_LARGE)
			return (pool);
		*old = pool;
		pool = (uint8_t *)res;
		res = *((uint64_t*)(pool + g_malloc.bytesz[type]));
	}
	if (type != LARGE && find_ptr(pool, to_find, type) != NULL)
		return (pool);
	if (type == LARGE && to_find == pool + HEADER_LARGE)
		return (pool);
	return (NULL);
}

void				free(void *ptr)
{
	int		type;
	void	*pool;
	uint8_t	*old_pool;

	type = 0;
	old_pool = NULL;
	if ((uint64_t)ptr == 0)
		return ;
	if ((VERBOSE & 0x02) == 0x02)
		ft_strhexout("free ptr : ", (uint64_t)ptr);
	while (type < NB_AREA)
	{
		if (type == LARGE)
			free_large(ptr);
		else if ((pool = find_pool(ptr, &old_pool, type)) != NULL)
		{
			free_zone(pool, old_pool, ptr - g_malloc.mtdata[type], type);
			break ;
		}
		type++;
	}
}
