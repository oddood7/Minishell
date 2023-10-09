/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:12:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 19:06:41 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	handle_sig(int s)
// {
// 	int *rv;

// 	rv = rv_static(NULL);
// 	if (s == SIGINT)
// 	{
// 		*rv = 130;
// 		ft_putchar_fd('\n', 1);
// 		rl_on_new_line();
// 		//rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int	g_error;

void	code_error(int code)
{
	g_error = code;
}

void	signal_handler(int sig)
{
	if (rl_done && g_error == 2)
	{
		printf("\n");
		code_error(130);
	}
	if (!rl_done)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		code_error(130);
	}
	else if (sig == 3)
	{
		printf("Quit (core dumped)\n");
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
	printf("Exit Minishell with CTRL-D");
	free_kill(mini);
	clear_history();
	exit(0);
}
