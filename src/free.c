/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:33:07 by rostroh           #+#    #+#             */
/*   Updated: 2019/02/07 11:33:18 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int         look_addr(uint8_t *look_up, uint8_t *to_find)
{
    uint8_t         *last;
    uint16_t        val;

    look_up += 8;
    printf("J'assume 0X%lX\n", (unsigned long)look_up);
    if (look_up + 2 == to_find)
        return (1);
    val = read16in8(look_up);
    while (val != 0)
    {
        last = look_up;
        look_up += val + 2;
        if (look_up + 2 == to_find)
            return (1);
        val = read16in8(look_up);
    }
    printf("Cheh\n");
    return (0);
}

int         is_allocated(uint8_t *addr)
{
    uint64_t       tmp;
    uint8_t        *current;

    current = g_all_malloc.small;
    printf("Suis je dans la merde 0x%lX ?\n", (unsigned long)current);
    current += 2;
    tmp = read_size(current);
    if (tmp == 0)
        return (look_addr(current, addr));
    while (tmp != 0)
    {
        printf("En vie et 0X%llX\n", tmp);
        current = (uint8_t *)tmp + 2;
        printf("ON CHECK 0X%llX < 0X%llX < 0X%llX\n", (uint64_t)current, (uint64_t)addr, tmp);
        if ((uint64_t)current < (uint64_t)addr && (uint64_t)addr < tmp)
            return (look_addr(addr, current));
        tmp = read_size(current);

    }
    return (look_addr(current, addr));
}

void        free(void *ptr)
{
    uint8_t     *addr;

    addr = (uint8_t*)ptr;
    printf("\n\n\nOn veux free 0X%lX\n", (unsigned long)(addr));
    if (is_allocated(addr) == 0)
    {
        printf("Tu fous quoi abrutit !\n");
        exit(0);
    }
    else
        printf("Tu peux free, fait toi plez\n");
}
