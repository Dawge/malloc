/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:21 by rostroh           #+#    #+#             */
/*   Updated: 2019/01/21 19:33:27 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void        put_u16inu8(uint8_t *addr, uint16_t size)
{
    addr[0] = (uint8_t)(size >> 8);
    addr[1] = (uint8_t)(size);
}

uint16_t        read16in8(uint8_t *addr)
{
    uint16_t    val;

    val = ((uint16_t)addr[0] << 8) | ((uint16_t)addr[1]);
    return (val);
}

int         check_small_size(size_t size)
{
    uint64_t    *tmp;
    int         size_in_page;

    tmp = (uint64_t *)go_to_last_header((uint8_t *)g_all_malloc.small);
    size_in_page = *(tmp);
    if (size_in_page + size + 1 <= g_all_malloc.size_page * 16)
        return (1);
    return (-1);
}

uint8_t    *creat_block_small(uint8_t *ptr, uint16_t size)
{
    uint16_t    val;
    uint8_t    *tmp;
    //uint64_t    block;
    uint16_t    *put_size;

    put_size = (uint16_t *)ptr;
    *put_size += size + 2;
    printf("hey voici la size header %lu -------- %lu\n", (unsigned long)*put_size, (unsigned long)size);
    tmp = ptr + SIZE_HEADER;                               //first block size
    val = read16in8(tmp);
    while (val != 0)                            //parsing block
    {
        tmp += val + 2;
        val = read16in8(tmp);
        printf("addr ------- %lu & %lu\n", (unsigned long)tmp, (unsigned long)val);
    }
    //*tmp = size;
    put_u16inu8(tmp, size);
    //printf("tmp size %lu\n", (unsigned long)*tmp);
    return ((uint8_t*)(tmp + 1));
}


void        *creat_small(uint16_t size)
{
    uint8_t     *area;

    printf("Pas mieux\n");
    if (g_all_malloc.small == NULL)
    {
        printf("Go\n");
        g_all_malloc.small = mmap(0, g_all_malloc.size_page * 16, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        area = g_all_malloc.small;
        if (area == MAP_FAILED)
            return (NULL);
        creat_header((uint16_t*)area);
        area += SIZE_HEADER;
        put_u16inu8(area, size);
        area++;
    }
    else if (check_small_size(size) == -1)
    {
        printf("Hey mademoiselle\n");
        area = mmap(0, g_all_malloc.size_page * 16, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        write_next_area_addr((uint64_t)area, (uint8_t *)g_all_malloc.small);
        creat_header((uint16_t *)area);
        area += SIZE_HEADER;
    }
    else
    {
        area = go_to_last_header((uint8_t *)g_all_malloc.small);
        area = creat_block_small(area, size);
    }
    return (area);
}
