/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:39:31 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 13:21:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int for_unset(t_main *mini, char *str, int len)
{
	char **tab;

	tab = new_tab_env(mini, mini->env, str, len);
	dup_classic_env(mini, tab);
	mini->shell.error = 0;
	return (1);
}

void	do_for_exp(t_main *mini, char *str, int len)
{
	int i;
	char **tab;
	char *decla;

	i = 0;
	decla = ft_strjoin("declare -x ", str);
	while (mini->env_exp[i])
	{
		if (!ft_strncmp(mini->env_exp[i], decla, len + 11) && mini->env_exp[i][len + 11] == '=')
		{
			tab = new_tab_exp(mini, mini->env_exp, decla, len);
			dup_exp(mini, tab);
			break ;
		}
		i++;
	}
	free(decla);
	return ;
}

int	built_unset(t_main *mini, t_parsing *cmd)
{
	int i;
	int j;
	int len;

	i = 1;
	if (cmd->cmd_tab[i])
	{
		j = 0;
		len = ft_strlen(cmd->cmd_tab[i]);
		while (mini->env[j])
		{
			if (!ft_strncmp(mini->env[j], cmd->cmd_tab[i], len) && mini->env[j][len] == '=')
			{
				for_unset(mini, cmd->cmd_tab[i], len);
				break ;
			}
			j++;
		}
		do_for_exp(mini, cmd->cmd_tab[i], len);
	}
	mini->shell.error = 0;
	return (1);
}