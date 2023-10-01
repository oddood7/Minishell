/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:00:06 by lde-mais          #+#    #+#             */
/*   Updated: 2022/11/17 16:42:30 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*strsrc;
	unsigned char		*strdest;

	if (n == 0)
		return (dest);
	if (!dest && !src)
	{
		n = 0;
		return (NULL);
	}
	strsrc = (unsigned char *)src;
	strdest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		*strdest = *strsrc;
		strdest++;
		strsrc++;
		i++;
	}
	return (dest);
}
