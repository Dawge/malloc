/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:59:11 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 15:07:20 by rostroh          ###   ########.fr       */
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
# define SIZE_MASK 0x1FFF
# define IGNORE_FIRST 0x7FFF

# define VERBOSE 0
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
	uint8_t			init;
}					t_malloc;

t_malloc			g_malloc;

/*
**		area.c
*/
void				*handle(size_t size, int type);

/*
**		creat_area.c
*/
void				*creat_area(size_t size, int type);

/*
**		enlarge.c
*/
int					check_enlarge(uint8_t *ptr, size_t size, int type, \
		int ptr_type);

/*
**		free.c
*/
void				free(void *ptr);
int					get_type_mtdata(uint8_t *ptr);
void				*find_pool(uint8_t *to_find, uint8_t **old, int type);

/*
**		free_large.c
*/
void				free_large(uint8_t *ptr);

/*
**		malloc.c
*/
void				*malloc(size_t size);
int					get_type(size_t size);

/*
**		realloc.c
*/
void				*realloc(void *ptr, size_t size);

/*
**		release.c
*/
void				release_large(uint8_t *to_release, uint64_t size, \
		void *ptr, uint64_t next_addr);
uint64_t			free_zone(uint8_t *pool, uint8_t *old, void *ptr, int type);

/*
**		show_alloc_mem.c
*/
void				show_alloc_mem(void);

/*
**		tools.c
*/
void				ft_puthex(uint64_t nb);
void				ft_printaddr(uint8_t *ptr, int type);
void				ft_strintout(const char *str, int nb);
void				ft_strhexout(const char *str, uint64_t nb);

#endif
