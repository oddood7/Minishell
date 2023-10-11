/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:49:41 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 13:21:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	stop_arguments(char **tab, int i)
{
	while (tab[1][i])
	{
		if (ft_isalpha(tab[1][i]) || (tab[1][i] == '+' && i != 0))
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("exit :", 2);
			ft_putstr_fd(tab[1], 2);
			ft_putendl_fd(": argument need to be numerical", 2);
			return (2);
		}
		i++;
	}
	i = 0;
	while (tab[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("exit : too many arguments", 2);
		return (0);
	}
	ft_putendl_fd("exit", 1);
	return (ft_atoi(tab[1]));
}

int	built_exit(t_main *mini, t_parsing *parse)
{
	int j;

	j = 0;
	while (parse->cmd_tab[j])
		j++;
	if (j == 1)
	{
		ft_putendl_fd("exit", 1);
		mini->shell.error = 0;
	}
	else
	{
		j = stop_arguments(parse->cmd_tab, 0);
		if (j == 0)
		{
			mini->shell.error = 127;
			return (1);
		}
		else
			mini->shell.error = j;
	}
	resets(mini);
	free_kill(mini);
	exit (mini->shell.error);
}