/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:19 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 22:05:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	if full == 1, area is full. Otherwise, enought space for add malloc
*/
static uint8_t		*go_last_area(int type, int *full)
{
	uint8_t		ptr;
	uint64_t	res;

	ptr = 
	while (res != 0)
	{

	}
}

void				*handle_tiny(size_t size)
{
	int			full;
	uint8_t		*ptr;
	uint64_t	*res;

	full = 0;
	if (g_malloc.ptr_tiny == NULL)
		return (creat_area(size, TINY) + HEADER_SIZE + META_DATA);
	ptr = go_last_area(TINY, &full);
	if (full == 0)
	{
	}
	else
	{
		res = (uint64_t*)creat_area(size, TINY);
		*(uint64_t*)(ptr + SIZE_AREA) = (uint64_t)res;
	}
	return (NULL);
}

void				*handle_small(size_t size)
{
	if (g_malloc.ptr_small == NULL)
		return (creat_area(size, SMALL));
	return (NULL);
}

void				*handle_large(size_t size)
{
	if (g_malloc.ptr_large == NULL)
		return (creat_area(size, LARGE));
	return (NULL);
}
