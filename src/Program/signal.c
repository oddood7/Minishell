/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:12:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/13 17:02:24 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_error;

void	signal_handler(int sig)
{
	if (rl_done && g_error == 2)
	{
		ft_printf("\n");
		code_error(130);
	}
	if (!rl_done)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		code_error(130);
	}
	if (sig == 3)
	{
		ft_printf("Quit (core dumped)\n");
		code_error(131);
	}
	return ;
}

void	sig_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_eot(t_main *mini)
{
	ft_printf("Exit Minishell with CTRL-D\n");
	built_in_free(mini);
	clear_history();
	exit(0);
}
