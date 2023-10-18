/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:42:07 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/18 14:00:32 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*malloc_space(t_parsing *node, int i)
{
	int		size;
	char	*str;

	size = ft_strlen(node->cmd_tab[i]);
	str = ft_malloc(sizeof(char) * size + 1);
	return (str);
}

int	count_quotes(char *str, int quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == quote)
			j++;
		i++;
	}
	return (j);
}

char	*check_4_strim(t_parsing *node, int i, int quote)
{
	char	*new;
	int		len;

	len = ft_strlen(node->cmd_tab[i]);
	if (node->cmd_tab[i][0] == quote && \
	count_quotes(node->cmd_tab[i], quote) == 2 \
	&& node->cmd_tab[i][len - 1] == quote)
	{
		new = ft_trim(node->cmd_tab[i], quote);
		node->cmd_tab[i] = ft_strdup(new);
		return (new);
	}
	else
		return (NULL);
}

int	rm_quote(t_parsing *node, int index, int quote)
{
	char		*new;
	int			j;
	int			i;

	j = 0;
	i = 0;
	new = check_4_strim(node, i, quote);
	if (!new)
	{
		new = malloc_space(node, index);
		while (node->cmd_tab[index][j])
		{
			if (node->cmd_tab[index][j] == quote)
				j++;
			else
				new[i++] = node->cmd_tab[index][j++];
		}
		new[i] = '\0';
		node->cmd_tab[index] = ft_strdup(new);
	}
	if (quote == 39)
		return (1);
	return (0);
}

int	quotes(t_parsing *node, int i)
{
	int	j;

	j = 0;
	while (node->cmd_tab[i][j])
	{
		if (node->redirection)
			check_quote_redir(node->redirection);
		if (node->cmd_tab[i][j] == 39)
			return (rm_quote(node, i, 39));
		else if (node->cmd_tab[i][j] == 34)
			return (rm_quote(node, i, 34));
		j++;
	}
	return (0);
}
