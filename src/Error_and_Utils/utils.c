/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:37:14 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/13 17:10:51 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_rchar(char c, char v)
{
	if (c == v)
		return (1);
	return (0);
}

int ft_size_list(t_lexer *list)
{
	int i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void    resets(t_main *mini)
{
    if (mini->input_line)
        free(mini->input_line);
    if (mini->lexer_list)
        ft_free_lexer(mini->lexer_list);
    mini->lexer_list = NULL;
    if (mini->syntaxe_check == 0)
    {
        if (mini->cmd_parse)
            free_cmd_tab(mini);
        if (mini->cmd_parse)
            free_cmd_lst(mini->cmd_parse);
    }
    mini->syntaxe_check = 0;
    mini->cmd_parse = NULL;
	sig_init();
}

void    free_kill(t_main *mini)
{
    ft_free_tab(mini->env);
    mini->env = NULL;
 	ft_free_tab(mini->env_exp);
    mini->env_exp = NULL;
}

/*
 * Compare 2 string
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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
