/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:25:23 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/18 20:59:29 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*check_area(uint8_t *ptr, uint8_t *to_find)
{
	uint64_t	size_area;


}

void			*find_ptr(void *to_find)
{
	int			i;
	uint8_t		*ptr;

	i = 0;
	while (i < NB_AREA)
	{
		if ((ptr = check_area(g_malloc.ptr[i], to_find)) != NULL)
			return (ptr);
		i++;
	}
	return (NULL);
}

void			free(void *ptr)
{
	if (find_ptr(ptr) == NULL)
		return ;
}
