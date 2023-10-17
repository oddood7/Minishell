/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:09:25 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 14:43:33 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Program stop.
 * Fonction a l'image de 'exit' 
 * Quitte le programme proprement avec free.
 * :warning:
 * wait(100) supprime de la premiere ligne pour la norme
*/
int	ft_exit(t_main *mini, t_parsing *parse)
{
	long long int	code_err;

	code_err = 0;
	ft_printf("exit\n");
	if (mini == NULL || parse == NULL)
		code_err = EXIT_FAILURE;
	else if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1] \
		&& is_numeric(parse->cmd_tab[parse->incr +1]) == 1)
	{
		ft_printf("%s: %s: numeric argument required\n", parse->cmd_tab[parse->incr],
			parse->cmd_tab[parse->incr +1]);
		code_err = 2;
	}
	else if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1] \
		&& parse->cmd_tab[parse->incr +2])
	{
		ft_printf("%s: too many arguments\n", parse->cmd_tab[parse->incr]);
		mini->shell.error = handle_error_bis(1);
		return (1);
	}
	else if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1])
	{
		code_err = ft_long_atoi(parse->cmd_tab[parse->incr +1]);
		if (ft_strcmp(parse->cmd_tab[parse->incr +1], ft_long_itoa(code_err)) != 0)
		{
			ft_printf("%s: %s: numeric argument required\n", parse->cmd_tab[parse->incr],
				parse->cmd_tab[parse->incr +1]);
			code_err = 2;
		}
		else
			code_err %= 256;
	}
	else if (mini->shell.error == 0 && g_error != 0)
		code_err = g_error;
	else
		code_err = mini->shell.error;
	free_garbage();
	exit(code_err);
}
