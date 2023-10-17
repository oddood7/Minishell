/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:54:40 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 18:54:40 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_process(t_main *mini)
{
	int	i;

	i = 0;
	if (mini->hd_count)
	{
		while (i < mini->hd_count)
		{
			if (mini->here_doc[i].fd[0] > -1)
				close(mini->here_doc[i].fd[0]);
			i++;
		}
	}
}

void	wait_exec(t_main *mini)
{
	int	i;
	int	status;

	i = 0;
	if (ft_strcmp("./minishell", mini->cmd_parse->cmd_tab[0]) != 0)
	{
		signal(SIGQUIT, signal_handler);
		g_error = 2;
	}
	waitpid(mini->pid_last, &status, 0);
	while (i < mini->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	signal(SIGQUIT, SIG_IGN);
	if (g_error == 2)
		g_error = 0;
	if (g_error != 0)
		mini->shell.error = g_error;
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		mini->shell.error = handle_error_bis(WEXITSTATUS(status));
	else if (WIFEXITED(status) && WTERMSIG(status) == SIGSEGV)
	{
		ft_printf("Segmentation Fault (core dumped)\n");
		mini->shell.error = handle_error_bis(139);
	}		
	else
		mini->shell.error = handle_error_bis(0);
}

void	exit_error_redir(t_main *mini, int fd[2])
{
	(void)(mini);
	if (fd[0] > 1)
		close (fd[0]);
	if (fd[1] > 1)
		close(fd[1]);
	exit (1);
}

int	close_error(int in, int out)
{
	if (in > 1)
		close (in);
	if (out > 1)
		close (out);
	return (-2);
}
