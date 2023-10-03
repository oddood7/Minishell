/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/03 16:37:23 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *find_var(t_list *env, char *var)
{
	char *tmp;
	int len;

	len = ft_strlen(tmp);
	while (env)
	{
		if (!ft_strncmp(tmp, env->var, len) && (env->var[len] == '=' || env->var[len] == '\0'))
		{
			tmp = env->var;
			return (tmp);
		}
		env = env->next;
	}
	return (NULL);
}

char	*get_var_name(char *str, t_main *mini)
{
	char *tmp;
	int i;

	i = 0;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		err_mall(mini);
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}