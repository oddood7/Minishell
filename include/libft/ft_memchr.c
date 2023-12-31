/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:03:59 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/12 17:04:01 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}

/* int main()
{
	char str[10] = "bonjour";
	int c = 't';
	int size = 7;
	ft_printf("%p\n", memchr(str, c, size));
	ft_printf("%p", ft_memchr(str, c, size));
}*/
