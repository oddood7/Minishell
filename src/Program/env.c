/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:37:01 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/29 23:02:26 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*get_env_list(char **env)
{
	t_list *env;
	int i;

	i = 1;
	if (env[0])
	{
		env = ft_lstnew(env[0]);
		while (env[i++])
			ft_lstadd_back(&env, ft_lstnew(env[i]));
		return (env);
	}
	else
		return (NULL);
}

void get_env_tab(t_list *env, t_main *mini)
{
	int i;

	i = 0;
	mini->env = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!mini->env)
		err_mall(mini);
	while (env)
	{
		mini->env[i] = env->var;
		env = env->next;
		i++;
	}
	mini->env[i] = 0;
}

int    dup_env(t_main *mini, char *tmp, int i)
{
    int        j;
    int        k;

    j = 0;
    k = 0;
    while (mini->env[i][j] != '=')
    {
        tmp[j] = mini->env[i][j];
        j++;
        k++;
    }
    tmp[k++] = '=';
    tmp[k++] = '"';
    j++;
    while (mini->env[i][j])
    {
        tmp[k] = mini->env[i][j];
        j++;
        k++;
    }
    tmp[k++] = '"';
    return (k);
}

void	get_env_export(t_main *mini)
{
	int i;
	char *add;

	i = 0;
	add = "declare -x ";
	while (mini->env[i])
		i++;
	mini->env_exp = malloc(sizeof(char *) * i + 1);
	if (!mini->env_exp)
		err_mall(mini);
	i = 0;
	env_export2(mini, add);
}

void	env_export2(t_main *mini, char *add)
{
	int i;
	int j;
	int len;
	char *tmp;

	i = 0;
	while (mini->env[i])
	{
		j = 0;
		len = ft_strlen(mini->env[i]);
		tmp = malloc(sizeof(char) * (len + 2) + 1);
		if (!tmp)
			err_mall(mini);
		j += dup_env(mini, tmp, i);
		tmp[j] = '\0';
		mini->env_exp[i] = ft_strjoin(add, tmp);
		free(tmp);
		i++;
	}
	mini->env_exp[i] = 0;
}