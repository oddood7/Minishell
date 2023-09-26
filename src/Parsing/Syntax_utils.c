/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:20:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/27 00:29:32 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	err_syn(t_main *mini, char *str)
{
	ft_putstr_fd("shell : syntax error ", 1);
	ft_putendl_fd(str, 1);
	mini->return_value = 2;
	return (1);
}

int	two_pipes(t_main *mini, t_lexer *ongoing)
{
	if (ongoing->operateur == PIPE)
	{
		if (ongoing->next->operateur == PIPE)
			return (err_syn(mini, "parse error near '||'"));
	}
	return (0);
}