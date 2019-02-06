/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:40:28 by rostroh           #+#    #+#             */
/*   Updated: 2019/01/15 22:40:39 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void        print_tiny(void)
{
    uint8_t     *end;
    uint8_t     *addr;
    uint8_t     size;
    uint64_t    total;
    uint64_t    tmp;

    addr = g_all_malloc.tiny;
    printf("TINY: 0x%lX\n", (unsigned long)addr);
    tmp = read_size(addr);
    total = 0;
    while (tmp != 0)
    {
        printf("-------------- New Area --------------\n");
        tmp = read_size(addr + 2);
        addr += 10;                                                       //on passe sur la size
        while (*addr != 0)                                               //parsing block
        {
            total += *(addr);
            size = *(addr);
        //    printf("Size = %d\n", size);
            end = addr + size;
            printf("0x%lX - 0x%lX : %u octets\n", (unsigned long)(addr + 1), (unsigned long)(end + 1), *addr);
            addr += *addr + 1;
        }
        addr = (uint8_t *)tmp;
    }
    printf("Total: %llu octets\n", total);
}

void        print_small(void)
{
    uint8_t     *end;
    uint8_t     *addr;
    uint16_t     size;
    uint64_t    total;
    uint64_t    tmp;

    addr = g_all_malloc.small;
    printf("SMALL: 0x%lX\n", (unsigned long)addr);
    tmp = read_size(addr);
    total = 0;
    while (tmp != 0)
    {
        printf("-------------- New Area --------------\n");
        tmp = read_size(addr + 2);
        addr += 10;                                                       //on passe sur la size
        while (*addr != 0)                                               //parsing block
        {
            total += *(addr);
            size = (uint16_t)*(addr);
        //    printf("Size = %d\n", size);
            end = addr + size;
            printf("0x%lX - 0x%lX : %u octets\n", (unsigned long)(addr + 1), (unsigned long)(end + 1), size);
            addr += *addr + 1;
        }
        addr = (uint8_t *)tmp;
    }
    printf("Total: %llu octets\n", total);
}

void        print_large(void)
{
    ;
}

void        order_print(int *f, int *s, int *t)
{
    if (g_all_malloc.tiny < g_all_malloc.small)
    {
        if (g_all_malloc.tiny < g_all_malloc.large)
        {
            *f = 0;
            if (g_all_malloc.small < g_all_malloc.large)
            {
                *s = 1;
                *t = 2;
            }
            else
            {
                *s = 2;
                *t = 1;
            }
        }
        else
        {
            *f = 2;
            *s = 0;
            *t = 1;
        }
    }
}

void        show_alloc_mem(void)
{/*
    int             print_first;
    int             print_second;
    int             print_third;
    static void		(*command_func[])(void) = {&print_tiny, &print_small, &print_large};

    command_func[]*/
   // print_tiny();
    print_small();
    print_large();
}
