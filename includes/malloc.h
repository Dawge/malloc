/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 22:49:17 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/04 15:33:21 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "ft_printf.h"
# include "sys/mman.h"

#define SIZE_HEADER 10

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

typedef struct		s_malloc
{
	size_t			size_page;
	size_t			tiny_size;
	size_t			small_size;
	void			*tiny;
	void			*small;
	void			*large;
}					t_malloc;

t_malloc			g_all_malloc;

void                *creat_tiny(uint8_t size);
uint8_t             *go_to_last_header(uint8_t *header);
void                write_next_area_addr(uint64_t next_addr, uint8_t *header);
void                *creat_small(uint16_t size);
uint64_t            read_size(uint8_t *addr);
void                creat_header(uint16_t *ptr);

#endif
