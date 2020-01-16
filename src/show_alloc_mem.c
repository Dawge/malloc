/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:18:40 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 14:52:09 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			ft_printmem(uint8_t *ptr, int ptrsz)
{
	int			i;

	i = 1;
	ft_puthex((uint64_t)ptr);
	ft_putchar('\t');
	while (i < ptrsz + 1)
	{
		if (ptr[i - 1] < 16)
			ft_putchar(' ');
		ft_puthex((uint64_t)ptr[i - 1]);
		ft_putchar(' ');
		if (i % 16 == 0 && i != ptrsz)
		{
			ft_putchar('\n');
			ft_puthex((uint64_t)(ptr + i));
			ft_putchar('\t');
		}
		i++;
	}
	ft_putstr("\n\n");
}

static void			print_addr(uint8_t *ptr, uint64_t size)
{
	ft_puthex((uint64_t)ptr);
	ft_putstr(" - ");
	ft_puthex((uint64_t)(ptr + size));
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
	if (DUMP == 1)
		ft_printmem(ptr, size);
}

static void			show_pool(uint8_t *ptr, int type)
{
	uint16_t		allocsz;

	if (type == LARGE)
		print_addr(ptr, *(uint64_t*)ptr);
	else
	{
		ptr += HEADER_SIZE;
		allocsz = *(uint16_t*)ptr & SIZE_MASK;
		print_addr(ptr + g_malloc.mtdata[type], allocsz);
		while (allocsz != 0)
		{
			ptr += allocsz + g_malloc.mtdata[type];
			allocsz = *(uint16_t*)ptr & SIZE_MASK;
			if (allocsz != 0)
				print_addr(ptr + g_malloc.mtdata[type], allocsz);
		}
	}
}

static void			show_mem(uint8_t *ptr, int type)
{
	uint64_t		next_pool;

	next_pool = *(uint64_t*)(ptr + g_malloc.bytesz[type]);
	show_pool(ptr, type);
	while (next_pool != 0)
	{
		ptr = (uint8_t*)next_pool;
		next_pool = *(uint64_t*)(ptr + g_malloc.bytesz[type]);
		show_pool(ptr, type);
	}
}

void				show_alloc_mem(void)
{
	int				i;
	static char		*type_name[NB_AREA] = {"TINY", "SMALL", "LARGE"};

	i = 0;
	while (i < NB_AREA)
	{
		ft_putstr(type_name[i]);
		if (g_malloc.ptr[i] != NULL)
		{
			ft_strhexout(" : ", (uint64_t)g_malloc.ptr[i]);
			show_mem(g_malloc.ptr[i], i);
		}
		i++;
		ft_putchar('\n');
	}
}
