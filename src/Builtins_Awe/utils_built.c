/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:30:00 by asalic            #+#    #+#             */
/*   Updated: 2023/10/13 17:12:09 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Check si getenv est NULL
 * Si oui, renvoit une chaine vide
 * Renvoit un char * de la valeur de la ve enregistree
*/
char *get_env_var(const char *name)
{
	char	*env_var;

	env_var = getenv(name);
	if (! env_var)
		env_var = "";
	return (ft_strdup(env_var));
}

/* 
 * Creer les maillons shell->str en fonction de getenv
 * Check cas d'erreurs
*/
int	handle_env(t_main *mini)
{
	mini->shell.home = get_env_var("HOME");
	mini->shell.user = get_env_var("USER");
	mini->shell.pwd = get_env_var("PWD");
	mini->shell.is_pwd = get_env_var("PWD");
	mini->shell.is_oldpwd = get_env_var("OLDPWD");
	mini->shell.oldpwd = get_env_var("OLDPWD");
	mini->shell.path = get_env_var("PATH");
	mini->shell.shlvl = get_env_var("SHLVL");
	mini->shell.error = 0;
	if (mini->shell.path != NULL && mini->shell.path[0] != '\0')
	{
		mini->shell.cmd_paths = ft_split(mini->shell.path + 5, ':');
		if (! mini->shell.cmd_paths)
			return (-1);
	}
	return (0);
}

/* 
 * Fonction d'extension de cd.
 * Permets de mettre a jour ou d'export pwd et oldpwd lorsque cd change
 * de repertoire.
*/
int	cd_move_and_change(t_main *mini)
{
	char	*old_pwd_change;
	char	*old_cmd;
	char	*current_cmd;
	char	*new_pwd;
	char	*tmp;

	old_pwd_change = ft_strjoin("OLDPWD=", mini->shell.is_pwd);
	if (!old_pwd_change)
		return (1);
	old_cmd = ft_strjoin("OLDPWD=", mini->shell.is_oldpwd);
	if (!old_cmd)
	{
		free(old_pwd_change);
		return (1);
	}
	change_env_cd(&mini->env_list, old_pwd_change, old_cmd);
	free(old_cmd);
	free(old_pwd_change);
	free(mini->shell.is_oldpwd);
	free(mini->shell.oldpwd);
	mini->shell.is_oldpwd = ft_strdup(mini->shell.is_pwd);
	mini->shell.oldpwd = ft_strdup(mini->shell.is_pwd);
	tmp = getcwd(NULL, 0);
	current_cmd = ft_strdup(tmp);
	free(tmp);
	if (current_cmd != NULL)
	{
		new_pwd = ft_strjoin("PWD=", current_cmd);
		if (!new_pwd)
		{
			free(current_cmd);
			return (1);
		}
		old_cmd = ft_strjoin("PWD=", mini->shell.is_pwd);
		if (!old_cmd)
		{
			free(current_cmd);
			free(new_pwd);
			return (1);
		}
		change_env_cd(&mini->env_list, new_pwd, old_cmd);
		free(mini->shell.pwd);
		free(mini->shell.is_pwd);
		mini->shell.is_pwd = ft_strdup(current_cmd);
		mini->shell.pwd = ft_strdup(current_cmd);
		free(current_cmd);
		free(new_pwd);
		free(old_cmd);
	}
	else
		return (1);
	mini->env = env_to_char(&mini->env_list);
	return (0);
}
