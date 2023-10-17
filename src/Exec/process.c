/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:55:19 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 18:55:19 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_ex(t_main *mini, int fd[2], int old_fd[2], int *i)
{
	fd[0] = 0;
	fd[1] = 0;
	old_fd[0] = -1;
	old_fd[1] = -1;
	mini->hd_pos = 0;
	*i = 0;
}

int	last_redir(t_main *mini, t_parsing *node, int *in, int *out)
{
	t_lexer	*tmp;

	node->hd_check = 0;
	tmp = node->redirection;
	while (node->redirection)
	{
		last_redir0(mini, node, in, out);
		if (last_redir2(mini, node, in, out) == -2)
		{
			node->redirection = tmp;
			return (-2);
		}
		node->redirection = node->redirection->next;
	}
	node->redirection = tmp;
	return (0);
}

void	last_process(t_main *mini, t_parsing *node, char *cmd, int fd[2])
{
	close_hds(mini, node);
	if (last_redir(mini, node, &fd[0], &fd[1]) == -2)
		exit_error_redir(mini, fd);
	if (fd[0] && node->hd_check == 0)
	{
		if (fd[1] > 1)
			close(fd[1]);
		dup2(fd[0], 0);
		if (fd[0] > 1)
			close(fd[0]);
	}
	find(mini, node);
	cmd = get_command(mini, mini->cmd_paths, node->cmd_tab[0]);
	if (cmd == NULL)
		no_command(mini, node);
	signal(SIGQUIT, signal_handler);
	execve(cmd, node->cmd_tab, mini->env);
	free_garbage();
	exit (1);
}
