/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:33:53 by rostroh           #+#    #+#             */
/*   Updated: 2020/01/11 15:31:37 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "include/malloc.h"

#define FAT_ALLOC 1
#define FREE_1 2
#define FREE_2 3
#define FREED_ZONE 4
#define FAT_FREE 5
#define MTDATA_TYPE 6
#define REALLOC_EZ 7
#define MALLOC_CONTENT 8

#define TEST MALLOC_CONTENT

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

#if TEST == RELEASE_ONE
#define NB_ALLOC 100
int			main(void)
{
	int			i;
	char		*p1;

	i = 0;
	while (i < NB_ALLOC)
	{
		
		i++;
	}
	return (0);
}
#endif

#if TEST == MALLOC_CONTENT
#define S1 0x100
#define S2 0x100
int			main(void)
{
	char	*p1;
	char	*p2;

	p1 = malloc(sizeof(char) * S1);
	for (int i = 0; i < S1; i++)
		p1[i] = 0xff;
	p2 = malloc(sizeof(char) * S2);
	for (int i = 0; i < S2; i++)
		p2[i] = 0xef;
	show_alloc_mem();
}
#endif

#if TEST == REALLOC_EZ
int			main(void)
{
	char		*ptr;
	char		*ptr2;

	ptr = malloc(sizeof(char) * 10);
	ptr = realloc(ptr, 0x101);
	ptr = malloc(16);
}
#endif

#if TEST == MTDATA_TYPE
int			main(void)
{
	char		*ptr;

	ptr = malloc(sizeof(char) * 512);
	free(ptr);
	ptr = malloc(sizeof(char) * 2048);
	free(ptr);
	ptr = malloc(sizeof(char) * 6000);
	free(ptr);
}
#endif

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
			ptr[j] = 0xff;
	}
	return (0);
}
#endif
