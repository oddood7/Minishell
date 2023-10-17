/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:12:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:59:35 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_error;

void	help_loop(t_main *mini, char *input)
{
	if (!input)
		handle_eot(mini);
	if (g_error != 0)
	{
		mini->shell.error = g_error;
		g_error = 0;
	}
	mini->lexer_list = NULL;
	mini->cmd_parse = NULL;
}

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
	clear_history();
	free_garbage();
	exit(mini->shell.error);
}
