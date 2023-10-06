/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:12:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/06 00:23:27 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sig(int s)
{
	int *rv;

	rv = rv_static(NULL);
	if (s == SIGINT)
	{
		*rv = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_init(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_eot(t_main *mini)
{
	free_kill(mini);
	clear_history();
	exit(0);
}