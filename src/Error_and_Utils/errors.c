/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:59:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/13 17:02:29 by asalic           ###   ########.fr       */
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

void	code_error(int code)
{
	g_error = code;
}

int	handle_error_bis(int code_err)
{
	int	final_error;

	final_error = 0;
	if (code_err == 13 || code_err == 12)
		final_error = 126;
	else if (code_err == 11)
		final_error = 127;
	else if (code_err == 0 && g_error != 0)
		final_error = g_error;
	else
		final_error = code_err;
	return (final_error);
}

int    ft_perror(char *str)
{
    (void)str;
    ft_putendl_fd(" Is a directory", 2);
    return (1);
}