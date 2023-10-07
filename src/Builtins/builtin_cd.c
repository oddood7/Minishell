/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:26:51 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/07 15:32:11 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **get_tab(t_main *mini, char **tab, char *pwd, char *old)
{
	int i;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], "PWD", 3))
			tab[i] = ft_strdup(pwd);
		else if (!ft_strncmp(mini->env[i], "OLDPWD", 6))
			tab[i] = ft_strdup(old);
		else
			tab[i] = ft_strdup(mini->env[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}

void	change_path_env(t_main *mini, char *pwd, char *oldpwd)
{
	int i;
	char **tab;

	i = 0;
	pwd = ft_strjoin("PWD=", pwd);
	while (mini->env[i])
		i++;
	tab = malloc(sizeof(char *) * i + 1);
	if (!tab)
		err_mall(mini);
	tab = get_tab(mini, tab, pwd, oldpwd);
	ft_free_tab(mini->env);
	mini->env = malloc(sizeof(char *) * i + 1);
	if (!mini->env)
		err_mall(mini);
	while (tab[i++])
		mini->env[i] = ft_strdup(tab[i]);
	mini->env[i] = 0;
	ft_free_tab(tab);
	free(pwd);
}

void	change_path2(t_main *mini)
{
	char 		pwd[2048];
	char 		*oldpwd;
	int 		i;

	i = 0;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		handle_error(mini, "cwd failed", 1);
		return ;
	}
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], "PWD", 3))
			break ;
		i++;
		if (!mini->env[i])
			return ;
	}
	oldpwd = malloc(sizeof(char) * ft_strlen(mini->env[i]) + 1);
	if (!oldpwd)
		err_mall(mini);
	oldpwd = copy_pwd(mini, oldpwd, i);
	change_path_env(mini, oldpwd, pwd);
	free(oldpwd);
	change_path_exp2(mini, pwd);
}

void cd_no_args(t_main *mini)
{
	char *str;
	int i;
	
	i = 0;
	while (ft_strncmp(mini->env[i], "HOME", 4))
		i++;
	str = ft_substr(mini->env[i], 5, ft_strlen(mini->env[i]) - 5);
	chdir(str);
	free(str);
	return ;
}

int built_cd(t_main *mini, t_parsing *cmd)
{
	int i;
	if (!cmd->cmd_tab[1])
	{
		cd_no_args(mini);
		change_path2(mini);
		mini->return_value = 0;
		return (1);
	}
	if (arg_check(mini, cmd->cmd_tab))
		return (1);
	i = chdir(cmd->cmd_tab[1]);
	if (i == -1)
	{
		//perror("Error with chdir");
		ft_putstr_fd("cd :", 2);
		ft_putstr_fd(cmd->cmd_tab[1], 2);
		ft_putendl_fd(" : No such file or directory", 2);
		mini->return_value = 1;
		return (1);
	}
	else
		change_path2(mini);
	mini->return_value = 0;
	return (1);
}