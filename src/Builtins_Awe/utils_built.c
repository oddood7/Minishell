/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:30:00 by asalic            #+#    #+#             */
/*   Updated: 2023/10/18 13:57:32 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Check si getenv est NULL
 * Si oui, renvoit une chaine vide
 * Renvoit un char * de la valeur de la ve enregistree
*/
char	*get_env_var(const char *name)
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
		mini->shell.cmd_paths = ft_split(mini->shell.path + 5, ':');
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
	old_cmd = ft_strjoin("OLDPWD=", mini->shell.is_oldpwd);
	change_env_cd(&mini->env_list, old_pwd_change, old_cmd);
	mini->shell.is_oldpwd = ft_strdup(mini->shell.is_pwd);
	mini->shell.oldpwd = ft_strdup(mini->shell.is_pwd);
	tmp = getcwd(NULL, 0);
	current_cmd = ft_strdup(tmp);
	if (current_cmd != NULL)
	{
		new_pwd = ft_strjoin("PWD=", current_cmd);
		old_cmd = ft_strjoin("PWD=", mini->shell.is_pwd);
		change_env_cd(&mini->env_list, new_pwd, old_cmd);
		mini->shell.is_pwd = ft_strdup(current_cmd);
		mini->shell.pwd = ft_strdup(current_cmd);
	}
	else
		return (free(tmp), 1);
	mini->env = env_to_char(&mini->env_list);
	return (free(tmp), 0);
}

/* 
 * Change de repertoire en fonction du buf envoye.
 * Agit reellement comme la commande cd.
*/
int	cd_real_version(char *buf, t_main *mini, t_parsing *parse)
{
	if (chdir(buf) == -1)
	{
		ft_printf("%s: %s: %s\n", parse->cmd_tab[parse->incr], \
			buf, strerror(errno));
		return (errno);
	}
	else
	{
		if (!cd_move_and_change(mini))
			return (1);
	}
	return (0);
}

/* 
 * Boucle principale d'unset.
 * Cherche une VE et la supprime s'il la trouve.
*/
int	searchin_env(t_lexer **env_list, char *str)
{
	t_lexer	*current;
	t_lexer	*temp;
	char	*name_env;
	size_t	len;

	current = *env_list;
	len = ft_strlen(str);
	while (current && current->next)
	{
		name_env = ft_strdupto_n(current->next->str, '=');
		if (!name_env)
			return (1);
		if (ft_strncmp(str, name_env, len) == 0 && \
		len == ft_strlen(name_env))
		{
			temp = current->next->next;
			current->next->str = NULL;
			current->next = temp;
			return (0);
		}
		current = current->next;
	}
	return (1);
}
