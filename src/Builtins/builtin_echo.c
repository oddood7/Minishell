/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:31:36 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	n_check(char *str)
{
	int i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
		if (str[i] == '\0')
			return (0);
	}
	return (0);
}

void	print_echo(char **tab, int j)
{
	int i;

	i = 1;
	while (tab[i])
	{
		if (!j)
		{
			while (!n_check(tab[i]))
				i++;
		}
		ft_putstr_fd(tab[i], 1);
		i++;
		if (tab[i])
			ft_putchar_fd(' ', 1);
	}
	if (j)
		ft_putendl_fd(NULL, 1);
	return ;
}

int	built_echo(t_main *mini, t_parsing *parse)
{
	int i;

	i = 1;
	if (parse->cmd_tab[1])
	{
		if (!ft_strncmp(parse->cmd_tab[1], "-n", 2))
		{
			while (parse->cmd_tab[1][i] == 'n')
				i++;
			if (parse->cmd_tab[1][i] == '\0')
				print_echo(parse->cmd_tab, 0);
			else
				print_echo(parse->cmd_tab, 1);	
		}
		else
			print_echo(parse->cmd_tab, 1);
	}
	else if (!parse->cmd_tab[1])
		ft_putendl_fd(NULL, 1);
	mini->return_value = 0;
	return (0);
}