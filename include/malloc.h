/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:59:11 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 18:59:49 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "sys/mman.h"

# define TINY 1
# define SMALL 2
# define LARGE 3

# define TINY_SIZE 1024
# define SMALL_SIZE 4096

# define HEADER_SIZE 12
# define HEADER_LARGE 16

# define META_DATA 2
# define ALIGN_SIZE 16

# define VERBOSE 0

typedef struct		s_malloc
{
	uint8_t			*ptr_tiny;
	uint8_t			*ptr_small;
	uint8_t			*ptr_large;
	unsigned int	nb_page;
	size_t			pagesz;
}					t_malloc;

t_malloc			g_malloc;

void				*malloc(size_t size);

/*
**		area.c
*/

/*
**		tools.c
*/
void				ft_strintout(const char *str, int nb);
void				ft_strhexout(const char *str, int nb);
#endif
