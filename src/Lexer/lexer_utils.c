/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:05:01 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/08 16:42:07 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_trim_space(char const *s)
{
	char	*str;
	size_t	start;
	size_t	len;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && ft_whitespace(s[start]))
		start++;
	len = ft_strlen(&s[start]);
	if (len)
		while (s[start + len - 1] && ft_whitespace(s[start + len - 1]))
			len--;
	str = ft_substr(s, start, len);
	return (str);
}

void	clean_lexed_list(t_lexer **list)
{
	t_lexer *node;
	char	*trimmed;

	node = *list;
	while (node)
	{
		if (node->operateur == 0)
		{
			trimmed = ft_trim_space(node->str);
			free(node->str);
			node->str = trimmed;
		}
		node = node->next;
	}
}

char *trim_whitespace(char *str) 
{
    if (!str) 
		return (NULL);  
    char *end = str + ft_strlen(str) - 1;
    while(end > str && ft_whitespace((unsigned char)*end)) 
	{
		end--;
    	*(end+1) = 0;
	}
    while(*str && ft_whitespace((unsigned char)*str)) 
		str++;
    return str;
}
