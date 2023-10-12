/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:42:12 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/12 17:04:01 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i--;
	}
	return (0);
}
/*int	main()
{
	char str[100] = "bonjour";
	int	c = 'j';

	ft_printf("%s\n", strrchr(str, c));
	ft_printf("%s\n", ft_strrchr(str, c));
}*/