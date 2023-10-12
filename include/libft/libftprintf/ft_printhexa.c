/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:30:16 by asalic            #+#    #+#             */
/*   Updated: 2022/12/05 15:55:51 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_lenrest(long unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len ++;
	while (nb)
	{
		nb = nb / 16;
		len ++;
	}
	return (len);
}

int	ft_printhexa(long unsigned int nb, char *base)
{
	char				*rest;
	int					i;
	long unsigned int	nb1;
	int					len;

	len = 0;
	i = 0;
	nb1 = 0;
	len = ft_lenrest(nb);
	rest = malloc((len + 1) * sizeof(char));
	if (!rest)
		return (1);
	while (i < len)
	{
		nb1 = nb;
		nb = nb / 16;
		rest[i++] = base[nb1 % 16];
	}
	rest[i--] = '\0';
	while (i >= 0)
		write (1, &rest[i--], 1);
	free (rest);
	return (len);
}
