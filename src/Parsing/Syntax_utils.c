/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:20:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 13:21:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	err_syn(t_main *mini, char *str)
{
	ft_putstr_fd("shell : syntax error ", 1);
	ft_putendl_fd(str, 1);
	mini->shell.error = 2;
	return (1);
}

int	two_pipes(t_main *mini, t_lexer *ongoing)
{
	if (ongoing->operateur == PIPE)
	{
		if (ongoing->next->operateur == PIPE)
			return (err_syn(mini, "near unexpected token '||'"));
	}
	return (0);
}