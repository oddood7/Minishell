/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:09:25 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 16:37:21 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	err_not_numeric(t_parsing *parse)
{
	ft_printf("%s: %s: numeric argument required\n", \
	parse->cmd_tab[parse->incr],
		parse->cmd_tab[parse->incr +1]);
	return (2);
}

static int	what_kind_of_err(t_parsing *parse, t_main *mini, \
	long long int code)
{
	if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1])
	{
		code = ft_long_atoi(parse->cmd_tab[parse->incr +1]);
		if (ft_strcmp(parse->cmd_tab[parse->incr +1], \
			ft_long_itoa(code)) != 0)
			code = err_not_numeric(parse);
		else
			code %= 256;
	}
	else if (mini->shell.error == 0 && g_error != 0)
		code = g_error;
	else
		code = mini->shell.error;
	return (code);
}

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
		code_err = err_not_numeric(parse);
	else if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1] \
		&& parse->cmd_tab[parse->incr +2])
	{
		ft_printf("%s: too many arguments\n", parse->cmd_tab[parse->incr]);
		mini->shell.error = handle_error_bis(1);
		return (1);
	}
	else
		code_err = what_kind_of_err(parse, mini, code_err);
	free_garbage();
	exit(code_err);
}
