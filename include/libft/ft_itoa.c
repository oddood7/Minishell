/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:17:41 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/12 18:39:49 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbcount(int n)
{
	long int	nbr;
	int			nb;

	nbr = n;
	nb = 1;
	if (n < 0)
	{
		nb++;
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		nb++;
	}
	return (nb);
}

char	*ft_itoa(int n)
{
	long int		nbr;
	char			*str;
	int				i;

	str = malloc(sizeof(char) * (nbcount(n) + 1));
	if (!str)
		return (NULL);
	str[nbcount(n)] = '\0';
	i = nbcount(n) - 1;
	nbr = n;
	if (n < 0)
	{
		str[0] = '-';
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	str[i] = nbr + '0';
	return (str);
}
