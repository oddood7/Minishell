/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:23:11 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/06 17:05:15 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t    ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t    i;
    size_t    j;

    i = 0;
    j = 0;
    if (size > 0)
    {
        while (src[i] && i < (size))
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    while (src[j])
        j++;
    return (j);
}
