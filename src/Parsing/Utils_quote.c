/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:49:41 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/18 14:01:33 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_set(char c, int quote)
{
	if (c == quote)
		return (1);
	return (0);
}

char	*ft_trim(char const *s1, int quote)
{
	char		*str;
	size_t		start;
	size_t		end;
	size_t		i;

	start = 0;
	while (s1[start] && check_set(s1[start], quote))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1[end - 1], quote))
		end--;
	str = ft_malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*cpquote(char *s, int j, int quote)
{
	int		i;
	char	*ok;

	i = 0;
	ok = ft_malloc(sizeof(char) * ft_strlen(s) - count_quotes(s, quote) + 1);
	while (s[i])
	{
		if (s[i] == quote)
			i++;
		else
			ok[j++] = s[i++];
		if (s[i] == '\0')
		{
			ok[j] = '\0';
			break ;
		}
	}
	return (ok);
}

char	*rm_quote_redir(char *s, int quote, int j)
{
	char	*new;

	if (count_quotes(s, quote))
	{
		if (count_quotes(s, quote) == 2)
			new = ft_trim(s, quote);
		else
			new = cpquote(s, j, quote);
		return (new);
	}
	else
		return (NULL);
}

void	check_quote_redir(t_lexer *node)
{
	t_lexer	*tmp;
	char	*s_trim;

	tmp = node;
	while (tmp)
	{
		if (tmp->str)
		{
			if (count_quotes(tmp->str, 39))
			{
				s_trim = rm_quote_redir(tmp->str, 39, 0);
				tmp->str = s_trim;
			}
			else if (count_quotes(tmp->str, 34))
			{
				s_trim = rm_quote_redir(tmp->str, 34, 0);
				tmp->str = s_trim;
			}
		}
		tmp = tmp->next;
	}
}
