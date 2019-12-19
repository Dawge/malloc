/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:44:55 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/19 18:39:24 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				free_zone(void *pool, void *to_free, int type)
{
	uint64_t	size;

	size = *((uint16_t *)to_free) ^ g_malloc.mask[type];
	*((uint16_t*)(to_free)) |= FREE_MASK;
	ft_bzero(to_free + 2, size);
	return (1);
}
