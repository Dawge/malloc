/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:59:11 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/17 22:34:33 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "sys/mman.h"

# define TINY 0
# define SMALL 1
# define LARGE 2

# define TINY_SIZE 1024
# define SMALL_SIZE 4096

# define HEADER_SIZE 12
# define HEADER_LARGE 16

# define SIZE_AREA 4
# define SIZE_LARGE 8

# define META_DATA 2
# define META_LARGE 0

# define ALIGN_SIZE 16

# define VERBOSE 0

typedef struct		s_malloc
{
	uint8_t			*ptr[3];
	uint8_t			hdrsz[3];
	uint8_t			mtdata[3];
	uint32_t		maxsz[2];
	/*uint8_t			*ptr_tiny;
	uint8_t			*ptr_small;
	uint8_t			*ptr_large;*/
	unsigned int	nb_page;
	size_t			pagesz;
}					t_malloc;

t_malloc			g_malloc;

void				*malloc(size_t size);

/*
**		area.c
*/
void				*handle_tiny(size_t size);
void				*handle_small(size_t size);
void				*handle_large(size_t size);

/*
**		creat_area
*/
void				*creat_area(size_t size, int type);

/*
**		tools.c
*/
void				ft_strintout(const char *str, int nb);
void				ft_strhexout(const char *str, uint64_t nb);

/*
**		write_memory
*/
void				write_uint16(uint8_t *ptr, uint16_t data);
void				write_uint32(uint8_t *ptr, uint32_t data);
void				write_uint64(uint8_t *ptr, uint64_t data);

/*
**		read_memory
*/
uint16_t			read_uint16(uint8_t *ptr, uint16_t data);
#endif
