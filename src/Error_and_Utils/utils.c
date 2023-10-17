/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:37:14 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 17:13:25 by asalic           ###   ########.fr       */
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

int	ft_size_list(t_lexer *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	resets(t_main *mini)
{
	mini->lexer_list = NULL;
	mini->syntaxe_check = 0;
	mini->cmd_parse = NULL;
	sig_init();
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
