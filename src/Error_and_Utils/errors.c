/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:59:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/29 18:01:59 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	err_mall(t_main *mini)
{
	ft_free_tab(mini->env);
	resets(mini);
	exit (1);
}

int	directory_err(t_main *mini, char *str, int ok)
{
	ft_putstr_fd(str, 2);
	if (ok)
	{
		mini->return_value = 127;
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	else
	{
		mini->return_value = 126;
		ft_putstr_fd(" : Is directory\n", 2);
	}
	return (1);
}

int	handle_error(t_main *mini, char *str, int rv)
{
	ft_putendl_fd(str, 2);
	if (rv == 2)
		mini->return_value = 2;
	else if (rv == 127)
		mini->return_value = 127;
	else
		mini->return_value = rv;
	return (1);
}