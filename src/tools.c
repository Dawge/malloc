/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:48:08 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 14:51:35 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static char		cal_hex(int remainder)
{
	if (remainder < 10)
		return (remainder + '0');
	else
		return (remainder - 10 + 'A');
}

void			ft_puthex(uint64_t nb)
{
	int			i;
	int			j;
	char		buf[25];
	char		tmp[25];

	i = 0;
	j = 0;
	ft_putstr("0x");
	if (nb == 0)
		ft_putchar('0');
	while (nb > 0)
	{
		buf[i] = cal_hex(nb % 16);
		nb = nb / 16;
		i++;
	}
	i--;
	while (i >= 0)
	{
		tmp[j] = buf[i];
		ft_putchar(tmp[j]);
		i--;
		j++;
	}
}

void			ft_strintout(const char *str, int nb)
{
	ft_putstr(str);
	ft_putnbr(nb);
	ft_putchar('\n');
}

void			ft_strhexout(const char *str, uint64_t nb)
{
	ft_putstr(str);
	ft_puthex(nb);
	ft_putchar('\n');
}

void			ft_printaddr(uint8_t *ptr, int type)
{
	uint16_t	ptrsz;
	uint64_t	largesz;

	if (type == LARGE)
	{
		largesz = *((uint64_t*)(ptr - HEADER_LARGE));
		ft_strhexout("Size : ", largesz);
		ft_puthex((uint64_t)ptr);
		ft_strhexout(" - ", (uint64_t)(ptr + largesz));
		ft_putchar('\n');
	}
	else
	{
		ptrsz = *((uint16_t*)(ptr - META_DATA)) & SIZE_MASK;
		ft_strhexout("Size : ", ptrsz);
		ft_puthex((uint64_t)ptr);
		ft_strhexout(" - ", (uint64_t)(ptr + ptrsz));
		ft_putchar('\n');
	}
}
