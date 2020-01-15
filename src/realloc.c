/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:54:18 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/15 16:42:56 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		check_size(uint8_t *ptr, size_t size, int type, int ptr_type)
{
	if (size <= (*(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]) & SIZE_MASK))
	{
		if (ptr_type == type)
			return (1);
	}
	return (0);
}

static void		cpy_data(uint8_t *dst, uint8_t *src, int dst_type, int src_type)
{
	int			i;
	uint16_t	dstsz;
	uint16_t	srcsz;

	i = 0;
	dstsz = *(uint16_t*)(dst - g_malloc.mtdata[dst_type]) & SIZE_MASK;
	srcsz = *(uint16_t*)(src - g_malloc.mtdata[src_type]) & SIZE_MASK;
	while (i < srcsz)
	{
	//	ft_strhexout("cpy data to : ", (uint64_t)(dst + i));
		dst[i] = src[i];
		i++;
		if (i == dstsz)
			break ;
	}
}

static int		check_enlarge(uint8_t *ptr, size_t size, int type, int ptr_type)
{
	uint16_t		ptrsz;
	uint16_t		freedsz;

	ptrsz = *(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]) & SIZE_MASK;
//	ft_strhexout("enlarge ptrsz = ", ptrsz);
	if (*(ptr + ptrsz) + g_malloc.mtdata[ptr_type] == 0)
	{
		//ft_strhexout("ptr = ", (uint64_t)ptr);
		//ft_strhexout("ptrsz = ", (uint64_t)ptrsz);
		//ft_strhexout("next ptr = ", (uint64_t)(ptr + ptrsz));
		*(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]) = size | g_malloc.mask[ptr_type];
		//ft_strhexout("Alo = ", *(uint16_t*)(ptr - g_malloc.mtdata[ptr_type]));
		return (1);
	}
	freedsz = *(ptr + ptrsz) & SIZE_MASK;
	if ((*(ptr + ptrsz) & FREE_MASK) == FREE_MASK && freedsz + ptrsz >= (int)size)
	{
//		ft_putstr("\n\nIL SE PASSE DES TRUCS\n\n");
		if (freedsz - size > ALIGN_SIZE + g_malloc.mtdata[type])
		{
			*(ptr - g_malloc.mtdata[ptr_type]) = size;
			*(ptr + ptrsz) = 0;
			*(ptr + size) = (freedsz - size) | FREE_MASK | g_malloc.mask[type];
		}
		else
		{
			*(ptr - g_malloc.mtdata[ptr_type]) = freedsz;
			*(ptr + ptrsz) = 0;
		}
		//ft_putstr("bruh\n");
		return (1);
	}
	return (0);
}

static void		*handle_realloc(void *ptr, size_t size, int type, int ptr_type)
{
	//int			val;
	uint8_t		*new_ptr;

	if (type == LARGE)
	{
		ft_putstr("realloc large\n");
		new_ptr = malloc(size);
		cpy_data(new_ptr, ptr, type, ptr_type);
		free(ptr);
	//	ft_putchar('\n');
		return (new_ptr);
	}
	//val = check_size(ptr, size, type, ptr_type);
	//if (val == 1)
	if (check_size(ptr, size, type, ptr_type) == 1)
	{
	//	ft_putstr("Fin realloc1\n\n");
		ft_putstr("Blanc sur rouge, rien ne bouge\n");
	//	ft_putchar('\n');
		return (ptr);
	}
	else if (type == ptr_type && check_enlarge(ptr, size, type, ptr_type) == 1)
	{
	//	ft_putstr("Fin realloc2\n\n");
		ft_putstr("Si on se sert, il y a de la place pour tout le monde\n");
//		ft_strhexout("Ici ca devrait aller\n", *(uint16_t*)(ptr - g_malloc.mtdata[type]));
	//	ft_putchar('\n');
		return (ptr);
	}
	else
	{
	//	ft_putstr("Fin realloc3\n\n");
		ft_putstr("Apres le probleme, c'est les autres\n");
		new_ptr = malloc(size);
		cpy_data(new_ptr, ptr, type, ptr_type);
		free(ptr);
	//	ft_putchar('\n');
		return (new_ptr);
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	int			type;
	int			ptr_type;
	uint8_t		*old;

	type = 0;
	ptr_type = 0;
	ft_strhexout("\nsalut realloc : ", (uint64_t)ptr);
	ft_strhexout("avec une size de : ", size);
	if (ptr == NULL)
	{
	//	ft_putchar('\n');
		return (malloc(size));
	}
	while (ptr_type < NB_AREA)
	{
		if (find_pool(ptr, &old, ptr_type) != NULL)
			break;
		ptr_type++;
	}
	if (ptr_type == NB_AREA)
	{
	//	ft_strhexout("LE BENEVOLE : ", (uint64_t)ptr);
		return (NULL);
	}
	type = get_type(size);
	ptr_type = get_type_mtdata(ptr);
	return (handle_realloc(ptr, size, type, ptr_type));
}
