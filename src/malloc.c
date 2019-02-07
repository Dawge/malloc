/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 22:32:09 by rostroh           #+#    #+#             */
/*   Updated: 2019/01/13 22:32:35 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void        init_global(void)
{
    g_all_malloc.size_page = getpagesize();
    g_all_malloc.tiny_size = (((g_all_malloc.size_page - 24) * 2) - 800) / 100;
    g_all_malloc.small_size = (((g_all_malloc.size_page - 24) * 16) - 800) / 100;
    printf("page size = %zu\n", g_all_malloc.size_page);
    printf("tiny size = %zu\n", g_all_malloc.tiny_size);
    printf("small size = %zu\n", g_all_malloc.small_size);
}

void		*malloc(size_t size)
{
    void    *ptr;

    //printf("Size = %d\n", size);
    if (g_all_malloc.small_size == 0 || g_all_malloc.tiny_size == 0)
        init_global();
    if (size < g_all_malloc.tiny_size)
        ptr = creat_tiny((uint8_t)size);
   else if (size < g_all_malloc.small_size)
   {
        //printf("Bah oui\n");
        ptr = creat_small((uint16_t)size);
    }
   else
        ;
//    /printf("ADR = 0X%lX\n", (unsigned long)ptr);
    return (ptr);
}
