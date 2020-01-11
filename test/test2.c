/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:32:00 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/11 15:31:33 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

void	print(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	int			i;
	char		*adr;

	i = 0;
	print("debutmain\n");
	while (i < 1024)
	{
		adr = (char *)malloc(1024);
		adr[0] = 42;
		free(adr);
		i++;
	}
	return (0);
}
