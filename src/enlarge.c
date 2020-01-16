/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enlarge.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:02:15 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 15:15:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_enlarge(uint8_t *ptr, size_t size, int type, int ptr_type)
{
	uint16_t		ptrsz;
	uint16_t		freedsz;

	ptrsz = *(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]) & SIZE_MASK;
	if (*(ptr + ptrsz) + g_malloc.mtdata[ptr_type] == 0)
	{
		*(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]) = \
			size | g_malloc.mask[ptr_type];
		return (1);
	}
	freedsz = *(ptr + ptrsz) & SIZE_MASK;
	if ((*(ptr + ptrsz) & FREE_MASK) == FREE_MASK && \
			freedsz + ptrsz >= (int)size)
	{
		*(ptr + ptrsz) = 0;
		if (freedsz - size > ALIGN_SIZE + g_malloc.mtdata[type])
		{
			*(ptr - g_malloc.mtdata[ptr_type]) = size;
			*(ptr + size) = (freedsz - size) | FREE_MASK | g_malloc.mask[type];
		}
		else
			*(ptr - g_malloc.mtdata[ptr_type]) += freedsz;
		return (1);
	}
	return (0);
}
