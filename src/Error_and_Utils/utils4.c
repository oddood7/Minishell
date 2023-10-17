/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:56:41 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 17:13:36 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_to_char(t_lexer **env_list)
{
	t_lexer	*current;
	char	**env_char;
	int		i;

	current = *env_list;
	env_char = ft_malloc(len_targs(current) * (sizeof * current));
	i = 0;
	while (current)
	{
		env_char[i] = ft_strdup(current->str);
		current = current->next;
		i ++;
	}
	env_char[i] = NULL;
	return (env_char);
}

/* Compte nombre de maillon dans une liste */
int	len_targs(t_lexer *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len ++;
		list = list->next;
	}
	return (len);
}

static int	nbcount(long long int n)
{
	long long int	nbr;
	long int		nb;

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

char	*ft_long_itoa(long long int n)
{
	long long int		nbr;
	char				*str;
	long long int		i;

	str = ft_malloc(sizeof(char) * (nbcount(n) + 1));
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

long long int	ft_long_atoi(const char *nptr)
{
	long long int	i;
	long long int	res;
	long long int	c;

	i = 0;
	c = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			c = c * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * c);
}
