/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_munmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:30:28 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 12:52:47 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "../libft/include/libft.h"

int			main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 10)
	{
		ft_putstr("ptr nb : ");
		ft_putnbr(i);
		ft_putchar('\n');
		addr = malloc(0x400);
		free(addr);
		i++;
	}
	return (0);
}
