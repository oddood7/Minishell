/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:37:01 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 14:58:59 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    var_copy(t_main *mini, char *tmp, int i)
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

void    get_env(t_main *mini, char **env)
{
    int    i;

    i = 0;
    set_env(mini, env);
    while (env[i])
        i++;
    mini->env = ft_malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env[i])
    {
        mini->env[i] = ft_strdup(env[i]);
        i++;
    }
    mini->env[i] = NULL;
}

int	print_env_exp(t_main *mini)
{
	int i;

	i = 0;
	while (mini->env_exp[i])
	{
		ft_putendl_fd(mini->env_exp[i], 1);
		i++;
	}
	mini->shell.error = 0;
	return (1);
}