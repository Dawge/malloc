/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:33:53 by rostroh           #+#    #+#             */
/*   Updated: 2019/12/20 19:07:09 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "include/malloc.h"

#define FAT_ALLOC 1
#define FREE_1 2
#define FREE_2 3
#define TEST FREE_2

#if TEST == FREE_2
#define SIZE 512
int			main(void)
{
	char		*p1;
	char		*p2;
	char		*p3;

	puts("\nDEBUT MAIN");
	p1 = malloc(SIZE);
	p2 = malloc(SIZE);
	p3 = malloc(SIZE);
	free(p2);
	free(p1);
	free(p3);
	return (0);
}
#endif

#if TEST == FREE_1
#define SIZE 512
int			main(void)
{
	char		*ptr;

	puts("\nDEBUT MAIN");
	ptr = malloc(SIZE);
	puts("MALLOC: OK");
	free(ptr);
	puts("FREE OK");
	return (0);
}
#endif

#if TEST == FAT_ALLOC
#define LOOP 5000
int			main(void)
{
	char		*ptr;

	for (int i = 0; i < LOOP; i++)
	{
		ptr = malloc(i);
		for (int j = 0; j < i; j++)
			ptr[j] = 0;
	}
	return (0);
}
#endif
