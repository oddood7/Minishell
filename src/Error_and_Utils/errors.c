/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:59:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 13:27:23 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	err_mall(t_main *mini)
{
	resets(mini);
	free_kill(mini);
	exit (1);
}

int	directory_err(t_main *mini, char *str, int ok)
{
	ft_putstr_fd(str, 2);
	if (ok)
	{
		mini->shell.error = 127;
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	else
	{
		mini->shell.error = 126;
		ft_putstr_fd(" : Is directory\n", 2);
	}
	return (1);
}

// int	handle_error(t_main *mini, char *str, int rv)
// {
// 	ft_putendl_fd(str, 2);
// 	if (rv == 2)
// 		mini->shell.error = 2;
// 	else if (rv == 127)
// 		mini->shell.error = 127;
// 	else
// 		mini->shell.error = rv;
// 	return (1);
// }

// int	err_export(char *str, int ok)
// {
// 	int i;

// 	i = 0;
// 	if (ok)
// 	{
// 		ft_putstr_fd("export : ", 2);
// 		while (str[i] && str[i] != '=')
// 		{	
// 			ft_putchar_fd(str[i], 2);
// 			i++;
// 		}
// 		ft_putstr_fd(" : not a valid argument\n", 2);
// 		return (1);
// 	}
// 	return (0);
// }

int    ft_perror(char *str)
{
    (void)str;
    ft_putendl_fd(" Is a directory", 2);
    return (1);
}