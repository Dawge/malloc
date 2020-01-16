/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:55:43 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/16 14:12:01 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int			main()
{
	char	*addr1;
	char	*addr3;

	addr1 = (char *)malloc(16 * M);
	strcpy(addr1, "bonjour\n");
	print(addr1);
	//addr3 = (char *)malloc(16 * M);
	addr3 = realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}
