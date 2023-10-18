/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:02:19 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/18 13:34:23 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rm_dollard(t_parsing *node, int i, int j)
{
	int		len_dol;
	char	*str_new;
	int		diff;
	int		tmp_j;

	len_dol = 0;
	tmp_j = j;
	while (node->cmd_tab[i][j] && node->cmd_tab[i][j] != ' ' \
	&& node->cmd_tab[i][j] != 39 && node->cmd_tab[i][++j] != '$')
		len_dol++;
	diff = ft_strlen(node->cmd_tab[i]) - len_dol;
	if (!diff)
	{
		node->cmd_tab[i] = ft_strdup("");
		return (0);
	}
	str_new = ft_malloc(sizeof(char) * (diff + 1));
	str_new = copy_without_dol(node, i, tmp_j, str_new);
	node->cmd_tab[i] = ft_substr(str_new, 0, diff);
	return (-1);
}

char	*copy_without_dol(t_parsing *node, int i, int j, char *s)
{
	int	k;

	k = 0;
	while (k < j)
	{
		s[k] = node->cmd_tab[i][k];
		k++;
	}
	while (node->cmd_tab[i][j] && node->cmd_tab[i][j] != ' ' \
	&& node->cmd_tab[i][j] != 39 && node->cmd_tab[i][++j] != '$')
	{
		if (!node->cmd_tab[i][j])
		{
			s[k] = '\0';
			return (s);
		}
	}
	while (node->cmd_tab[i][j])
	{
		s[k] = node->cmd_tab[i][j];
		j++;
		k++;
	}
	s[k] = '\0';
	return (s);
}

int	while_dol(t_main *mini, t_parsing *node, int i, int dol)
{
	int	len;
	int	j;

	len = 0;
	while (node->cmd_tab[i][dol] == '$')
	{
		dol++;
		if (node->cmd_tab[i][dol] == '\0')
			return (0);
		else if (node->cmd_tab[i][dol] != '$')
		{
			len = expanding_bis(mini, node, i, dol - 1);
			break ;
		}
	}
	if (len == 0)
		return (0);
	j = (dol - 1) + len;
	return (j);
}

int	check_env_bis(char **env, char *dollar)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(dollar);
	if (!check_qt(dollar))
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], dollar, len) && env[i][len] == '=')
				return (i);
			i++;
		}
		return (-1);
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], dollar, len - 1) && env[i][len - 1] == '=')
			return (420);
		i++;
	}
	return (-1);
}

int	check_env_var(t_main *mini, char *s, int j)
{
	char	*dollar;
	int		i;
	int		len;
	int		result;

	len = 0;
	if (s[j + 1] == '\0' || s[j + 1] == ' ')
		return (-2);
	if (s[j + 1] == '?')
		return (-3);
	i = j + 1;
	while (s[i] && s[i] != ' ' && s[i] != '$' && s[i] != '-' \
	&& s[i] != ':' && s[i] != '.')
	{
		i++;
		len++;
	}
	if (len == 1)
		dollar = ft_substr(s, j + 1, len);
	else
		dollar = ft_substr(s, j + 1, len);
	result = check_env_bis(mini->env, dollar);
	return (result);
}
