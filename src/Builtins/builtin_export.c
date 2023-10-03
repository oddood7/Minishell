/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:08 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/03 22:29:57 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// a revoir avec unset + export avec t_list

int	check_ex(t_main *mini, char *str)
{
	if (!ft_isalpha(str[0]) && str[0] != '\'' && str[0] != '\"' && str[0] != '_')
	{
		err_export(str, 1);
		mini->return_value = 1;
		return (1);
	}
	return (0);
}

t_list	*for_export(t_list *env, char *str, t_main *mini)
{
	char *var;

	if (check_ex(mini, str))
		return (env);
	var = get_var_name(str, mini);
	if (var)
	{
		if (!env)
			env = ft_lstnew(str);
		else if (!find_var(env, str))
			ft_lstadd_back(&env, ft_lstnew(str));
	}
	else if (!var && str)
	{
		if (!env)
			env = ft_lstnew(str);
		if (!find_var(env, str))
			ft_lstadd_back(&env, ft_lstnew(str));
	}
	free(var);
	mini->return_value = 0;
	return (env);
}

t_list	*export1(t_list *env, char **cmd, t_main *mini)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		env = for_export(env, cmd[i], mini);
		i++;
	}
	return (env);
}

t_list *built_export(t_list *env, t_main *mini)
{
	char **cmd;
	
	if (!cmd[1])
		get_env_export(mini);
	else
		env = export1(env, cmd, main);
	return (env);
}