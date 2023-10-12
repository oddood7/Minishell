/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:26:52 by asalic            #+#    #+#             */
/*   Updated: 2022/12/05 15:10:00 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	check_type(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'p')
		return (ft_addrhexa(va_arg(args, char *), 0));
	if (c == 'd' || c == 'i')
		return (ft_putnb(va_arg(args, int), 0));
	if (c == 'u')
		return (ft_putunb(va_arg(args, unsigned int), 0));
	if (c == 'x')
		return (ft_printhexa(va_arg(args, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_printhexa(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			len += check_type(args, format[++i]);
		else
		{
			write (1, &format[i], 1);
			len ++;
		}
		i ++;
	}
	va_end(args);
	return (len);
}
