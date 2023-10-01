/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:26:14 by lde-mais          #+#    #+#             */
/*   Updated: 2022/11/17 16:56:59 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	res = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size < ft_strlen(dest) + 1)
		return (size + ft_strlen(src));
	i = ft_strlen(dest);
	res = ft_strlen(src);
	if (size <= i)
		res = res + size;
	else
		res = res + i;
	while (src[j] != '\0' && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (res);
}

/* int	main()
{
	char *dst = "";
	char *src = "";
	int	size = 0;
	printf("%zu\n", strlcat(dst, src, size));
	printf("%zu", ft_strlcat(dst, src, size));
} */