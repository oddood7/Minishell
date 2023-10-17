/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:36:22 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 15:08:18 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *value_env_var(t_main *mini, char *str)
{
	char *tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)mini;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	i++;
	tmp = ft_malloc(sizeof(ft_strlen(str) - i + 1));
	while (str[i + j])
	{
		tmp[j] = str[i + j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	change_var_value(t_main *mini, char *new, char *old)
{
	int i;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], old, 5))
			break ;
		i++;
	}
	//free(mini->env[i]);
	mini->env[i] = ft_strdup(new);
}

char	*find_var_env(char **env, char *var)
{
	char *str;
	int i;
	int len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], len) && (env[i][len] == '='))
		{
			str = env[i];
			return (str);
		}
		i++;
	}
	return (NULL);
}