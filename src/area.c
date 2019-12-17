/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:19 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 17:49:42 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*handle_tiny(size_t size)
{
	if (g_malloc.ptr_tiny == NULL)
		return (creat_area(size, TINY));
	return (NULL);
}

void			*handle_small(size_t size)
{
	if (g_malloc.ptr_small == NULL)
		return (creat_area(size, SMALL));
	return (NULL);
}

void			*handle_large(size_t size)
{
	if (g_malloc.ptr_large == NULL)
		return (creat_area(size, LARGE));
	return (NULL);
}
