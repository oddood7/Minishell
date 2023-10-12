/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addrhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:46:24 by asalic            #+#    #+#             */
/*   Updated: 2022/12/05 15:55:29 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_addrhexa(void *str, int len)
{
	long unsigned int	p;

	if (!str)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	p = (long unsigned int) str;
	len += ft_putstr("0x");
	len += ft_printhexa(p, "0123456789abcdef");
	return (len);
}
