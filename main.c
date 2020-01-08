/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:33:53 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/08 18:28:45 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "include/malloc.h"

#define FAT_ALLOC 1
#define FREE_1 2
#define FREE_2 3
#define FREED_ZONE 4
#define FAT_FREE 5
#define TEST FREED_ZONE

#if TEST == FAT_FREE
#define LOOP 5000
int			main(void)
{
	char		*ptr[LOOP];

	for (int i = 0; i < LOOP; i++)
	{
		ptr[i] = malloc(i);
		for (int j = 0; j < i; j++)
			ptr[i][j] = 0;
	}
	for (int i = 0; i < LOOP; i++)
		free(ptr[i]);
	return (0);
}
#endif

#if TEST == FREED_ZONE
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
	p1 = malloc(SIZE);
	p2 = malloc(SIZE + 1);
	return (0);
}
#endif

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
