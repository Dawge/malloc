/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:54:18 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/08 22:54:11 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			check_size(uint8_t *ptr, size_t size, int type)
{
	if (size < *(ptr - g_malloc.mtdata[type]))
		return (1);
	return (0);
}

void		*realloc(void *ptr, size_t size)
{
	int			type;
	int			ptr_type;

	ft_strhexout("salut realloc : ", size);
	if (ptr == NULL)
		return (malloc(size));
	type = get_type(size);
	ptr_type = get_type_mtdata(ptr);
	if (check_size(ptr, size, ptr_type) == 1 && ptr_type == type)
		return (ptr);
	return (NULL);
}
