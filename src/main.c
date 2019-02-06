/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 23:09:50 by rostroh           #+#    #+#             */
/*   Updated: 2019/01/12 23:10:29 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"

int			main(void)
{
    int     i;
    char    *random;
    char    *ptr;
    char    *ptrCrash;

    i = 0;
    //printf("%llu %llu %llu\n", sizeof(size_t), sizeof(void *), sizeof(char));
    while (i < 250)
    {
        //printf("lj hifhe;oiheiohio hfo;hf;oie whoihewoi ;hefoihe wiohfiowhio heifoh %d\n", i);
        //printf("%d\n", i);
        random = (char *)malloc(sizeof(char) * 640);
        i++;
    }
  /*  ptr = (char *)malloc(sizeof(char) * 100);
//    ptrCrash = (char *)malloc(sizeof(char) * 5);
    i = 0;
    while (i < 15)
    {
     //   ptrCrash[i] = 'b';
        ptr[i] = 'a';
        i++;
    }
    //ptrCrash[4] = '\0';
    ptr[24] = '\0';
    ft_putendl(ptr);
    */
    //show_alloc_mem();
    //ft_putstr(ptrCrash);*/
	return (0);
}
