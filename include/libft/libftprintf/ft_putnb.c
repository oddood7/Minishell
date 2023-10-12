/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:20:36 by asalic            #+#    #+#             */
/*   Updated: 2022/12/05 15:56:10 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_lennb(int nb, int len)
{
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb = nb / 10;
		len ++;
	}
	return (len);
}

int	ft_putnb(int nb, int len)
{
	if (nb == -2147483648)
	{
		write (1, "-2", 2);
		len += 2;
		nb = 147483648;
	}
	else if (nb < 0)
	{
		write (1, "-", 1);
		len ++;
		nb = -nb;
	}
	len = ft_lennb(nb, len);
	if (nb >= 0 && nb <= 9)
	{
		nb = nb +48;
		write (1, &nb, 1);
	}
	else if (nb > 9)
	{
		ft_putnb(nb / 10, len);
		ft_putnb(nb % 10, len);
	}
	return (len);
}
