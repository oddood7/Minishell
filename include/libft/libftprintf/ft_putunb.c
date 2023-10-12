/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:58:06 by asalic            #+#    #+#             */
/*   Updated: 2022/12/05 15:06:42 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_lennb2(unsigned int nb, int len)
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

int	ft_putunb(unsigned int nb, int len)
{
	len = ft_lennb2(nb, len);
	if (nb <= 9)
	{
		nb = nb +48;
		write (1, &nb, 1);
	}
	else if (nb > 9)
	{
		ft_putunb(nb / 10, len);
		ft_putunb(nb % 10, len);
	}
	return (len);
}
