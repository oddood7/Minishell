/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:39:31 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/03 22:30:01 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// a revoir avec unset + export avec t_list

void	built_unset(t_main *mini, t_list *env)
{
	char **cmd;
	t_list *tmp;
	t_list *tmpbis;
	int i;

	tmp = env;
	i = 0;
	while (cmd[i++])
	{
		while (env->next)
		{
			if (!ft_strncmp(env->next->var, cmd[i], ft_strlen(cmd[i])))
			{
				tmpbis = env->next->next;
				free(env->next->var);
				free(env->next);
				env->next = tmpbis;
				break;
			}
			env = env->next;
		}
		env = tmp;
	}
	mini->return_value = 0;
}