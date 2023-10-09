/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:45:28 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **get_tabexp(t_main *mini, char **tabexp, char *pwd, char *old)
{
	int i;

	i = 0;
	while (mini->env_exp[i])
	{
		if (!ft_strncmp(mini->env_exp[i], "declare -x PWD", 3))
			tabexp[i] = ft_strdup(pwd);
		else if (!ft_strncmp(mini->env_exp[i], "declare -x OLDPWD", 6))
			tabexp[i] = ft_strdup(old);
		else
			tabexp[i] = ft_strdup(mini->env_exp[i]);
		i++;
	}
	tabexp[i] = 0;
	return (tabexp);
}

void	change_path_env_exp(t_main *mini, char *pwd, char *oldpwd)
{
	int i;
	char **tabexp;

	i = 0;
	while (mini->env_exp[i])
		i++;
	tabexp = malloc(sizeof(char *) * (i + 1));
	if (!tabexp)
		err_mall(mini);
	tabexp = get_tabexp(mini, tabexp, pwd, oldpwd);
	ft_free_tab(mini->env_exp);
	mini->env_exp = malloc(sizeof(char *) * (i + 1));
	if (!mini->env_exp)
		err_mall(mini);
	i = 0;
	while (tabexp[i])
	{
		mini->env_exp[i] = ft_strdup(tabexp[i]);
		i++;
	}
	mini->env_exp[i] = 0;
	ft_free_tab(tabexp);
}

void	change_path_exp2(t_main *mini, char *pwd)
{
	char 		*oldpwd;
	int 		i;

	i = 0;
	while (mini->env_exp[i])
	{
		if (!ft_strncmp(mini->env_exp[i], "declare -x PWD", 14))
			break ;
		i++;
	}
	oldpwd = malloc(sizeof(char) * ft_strlen(mini->env_exp[i]) + 1);
	if (!oldpwd)
		err_mall(mini);
	oldpwd = copy_declarex(mini, oldpwd, i);
	pwd = add_quote(mini, pwd);
	change_path_env_exp(mini, pwd, oldpwd);
	free(oldpwd);
	free(pwd);
}