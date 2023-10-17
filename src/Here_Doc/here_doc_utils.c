/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:14:13 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 15:04:56 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_here_doc	*return_hd(t_here_doc *here_doc)
{
	static t_here_doc	*hd;

	if (here_doc)
		hd = here_doc;
	return (hd);
}

int	return_hd_count(int hd_count)
{
	static int	hdc;

	if (hd_count != -1)
		hdc = hd_count;
	return (hdc);
}

t_main	*return_free_mini(t_main *mini)
{
	static t_main	*dr;

	if (mini)
		dr = mini;
	return (dr);
}

void	sig_hd(int signal)
{
	t_here_doc	*hd;
	int			i;
	int			hdc;
	t_main		*mini;

	mini = return_free_mini(NULL);
	if (signal == SIGINT)
	{
		i = 0;
		hd = return_hd(NULL);
		hdc = return_hd_count(-1);
		while (i < hdc)
		{
			if (hd[i].pos == 0)
				break ;
			close(hd[i].fd[0]);
			close(hd[i].fd[1]);
			i++;
		}
		free_garbage();
		exit (42);
	}
}

int	wait_hds(t_main *mini, int i)
{
	int	status;

	status = 0;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 42)
	{
		while (i >= 0)
		{
			close(mini->here_doc[i].fd[0]);
			close(mini->here_doc[i].fd[1]);
			i--;
		}
		signal(SIGINT, signal_handler);
		return (42);
	}
	return (0);
}