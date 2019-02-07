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

void        creat_header(uint16_t *ptr)          //header sur 10 oct
{
    *ptr = 10;                                   //nb oct in area sur 2 oct
    *(ptr + 1) = 0;                              //ptr next area sur 8 oct
}

void            put_size_tiny(uint16_t *ptr, uint8_t size)
{
    *ptr += size + 1;
}


uint64_t        read_size(uint8_t *addr)
{
    uint64_t     nu;

    nu = ((uint64_t)(addr)[0] << 56) | ((uint64_t)(addr)[1] << 48) | ((uint64_t)(addr)[2] << 40) | ((uint64_t)(addr)[3] << 32) | ((uint64_t)(addr)[4] << 24) | ((uint64_t)(addr)[5] << 16) | ((uint64_t)(addr)[6] << 8) | ((uint64_t)(addr)[7]);
    return (nu);
}

uint8_t        *creat_block(uint8_t *ptr, uint8_t size)
{
    uint8_t     *tmp;
    uint16_t    *put_size;

    put_size = (uint16_t *)ptr;
    *put_size += size + 1;
    tmp = ptr + SIZE_HEADER;                               //first block size
    while (*tmp != 0)                            //parsing block
    {
        tmp += *tmp + 1;
    }
    *tmp = size;
    return (tmp + 1);
}

uint8_t         *go_to_last_header(uint8_t *header)
{
    uint64_t    tmp;
    uint8_t     *addr;

    addr = header;
    addr += 2;
    tmp = read_size(addr);
    while (tmp != 0)
    {
        addr = (uint8_t *)tmp + 2;
        tmp = read_size(addr);
    }
    return (addr - 2);
}

int         check_tiny_size(size_t size)
{
    uint64_t    *tmp;
    int         size_in_page;

    tmp = (uint64_t *)go_to_last_header((uint8_t *)g_all_malloc.tiny);
    size_in_page = *(tmp);
    if (size_in_page + size + 1 <= g_all_malloc.size_page * 2)
        return (1);
    return (-1);
}

void        write_next_area_addr(uint64_t next_addr, uint8_t *header)
{
    int         i;
    int         offset;
    uint8_t     *addr;

    i = 0;
    offset = 56;
    addr = go_to_last_header(header) + 2;
    while (i < 8)
    {
        addr[i] = (uint8_t)(next_addr >> offset);
        i++;
        offset -= 8;
    }
}

void        *creat_tiny(uint8_t size)
{
    uint8_t        *area;

    if (g_all_malloc.tiny == NULL)
    {
        //printf("Go\n");
        g_all_malloc.tiny = mmap(0, g_all_malloc.size_page * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        area = g_all_malloc.tiny;
        if (area == MAP_FAILED)
            return (NULL);
        creat_header((uint16_t*)area);
        area += SIZE_HEADER;
        *area = size;
        area++;
    }
    else if (check_tiny_size(size) == -1)
    {
        printf("Wesh\n");
        area = mmap(0, getpagesize() * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        write_next_area_addr((uint64_t)area, (uint8_t *)g_all_malloc.tiny);
        creat_header((uint16_t *)area);
        area += SIZE_HEADER;
    }
    else
    {
        area = go_to_last_header((uint8_t *)g_all_malloc.tiny);
        area = creat_block(area, size);
    }
    return ((void *)(area));
}
