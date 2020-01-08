/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:59:11 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/06 19:58:47 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "sys/mman.h"

# define TINY 0
# define SMALL 1
# define LARGE 2
# define ERROR 0xFF
# define NB_AREA 3

/*
** Tiny = 0x400
** Small = 0x1000
*/
# define TINY_SIZE 1024
# define SMALL_SIZE 4096

# define HEADER_SIZE 12
# define HEADER_LARGE 16

# define SIZE_AREA 4
# define SIZE_LARGE 8

# define META_DATA 2
# define META_LARGE 0

# define ALIGN_SIZE 16

# define FREE_MASK 0x8000
# define TINY_MASK 0x4000
# define SMALL_MASK 0x2000
# define IGNORE_FIRST 0x7FFF

# define BIG_ADDR 0x7F7F00000000

# define VERBOSE 1
# define DUMP 0

typedef struct		s_malloc
{
	uint8_t			*ptr[NB_AREA];
	uint8_t			hdrsz[NB_AREA];
	uint8_t			mtdata[NB_AREA];
	uint8_t			bytesz[NB_AREA];
	uint32_t		mask[NB_AREA - 1];
	uint32_t		maxsz[NB_AREA - 1];
	unsigned int	nb_page;
	size_t			pagesz;
}					t_malloc;

t_malloc			g_malloc;

/*
**		malloc.c
*/
void				*malloc(size_t size);

/*
**		free.c
*/
void				free(void *ptr);

/*
**		area.c
*/
void				*handle(size_t size, int type);

/*
**		creat_area.c
*/
void				*creat_area(size_t size, int type);

/*
**		release.c
*/
uint64_t			free_zone(void *pool, void *ptr, int type);

/*
**		tools.c
*/
void				ft_printaddr(uint8_t *ptr, int type);
void				ft_strintout(const char *str, int nb);
void				ft_strhexout(const char *str, uint64_t nb);

#endif
