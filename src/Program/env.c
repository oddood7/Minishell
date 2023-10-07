/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:37:01 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/07 15:23:03 by lde-mais         ###   ########.fr       */
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

void    env_export_cpy(t_main *mini, char *decla)
{
    int        i;
    int        j;
    int        size;
    char    *tmp;

    i = 0;
    while (mini->env[i])
    {
        j = 0;
        size = ft_strlen(mini->env[i]);
        tmp = malloc(sizeof(char) * (size + 2) + 1);
        if (!tmp)
            err_mall(mini);
        j += var_copy(mini, tmp, i);
        tmp[j] = '\0';
        mini->env_exp[i] = ft_strjoin(decla, tmp);
        free(tmp);
        i++;
    }
    mini->env_exp[i] = 0;
}

void    get_env_export(t_main *mini)
{
    int        i;
    char    *decla;

    i = 0;
    decla = "declare -x ";
    while (mini->env[i])
        i++;
    mini->env_exp = malloc(sizeof(char *) * (i + 1));
    if (!mini->env_exp)
        err_mall(mini);
    i = 0;
    env_export_cpy(mini, decla);
}

void    get_env(t_main *mini, char **env)
{
    int    i;

    i = 0;
    while (env[i])
        i++;
    mini->env = malloc(sizeof(char *) * (i + 1));
    if (!mini->env)
        err_mall(mini);
    i = 0;
    while (env[i])
    {
        mini->env[i] = ft_strdup(env[i]);
        i++;
    }
    mini->env[i] = 0;
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
	mini->return_value = 0;
	return (1);
}