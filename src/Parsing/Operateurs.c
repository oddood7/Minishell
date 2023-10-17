/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operateurs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:11:52 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:02:56 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	single_handle(t_main *mini, t_lexer *ongoing)
{
	if (ongoing->operateur == RIGHT)
	{
		if (pipe_check(mini, ongoing))
			return (1);
		else if (right_check(mini, ongoing))
			return (1);
	}
	else if (ongoing->operateur == LEFT)
	{
		if (ongoing->next->operateur == PIPE)
		{
			if (ongoing->next->next && ongoing->next->next->operateur == PIPE)
				return (err_syn(mini, "near unexpected token '||'"));
			else
				return (err_syn(mini, "near unexpected token '|'"));
		}
		else if (left_check(mini, ongoing))
			return (1);
	}
	return (0);
}

int	double_handle(t_main *mini, t_lexer *ongoing)
{
	if (ongoing->operateur == RIGHT_RIGHT)
	{
		if (right2_check(mini, ongoing))
			return (1);
	}
	else if (ongoing->operateur == LEFT_LEFT)
	{
		if (left2_check(mini, ongoing))
			return (1);
	}
	return (0);
}

int	operateur_handle(t_main *mini)
{
	t_lexer	*ongoing;

	ongoing = mini->lexer_list;
	if (ongoing->operateur == PIPE)
	{
		if (ongoing->next && ongoing->next->operateur == PIPE)
			return (err_syn(mini, "near unexpected token '||'"));
		else
			return (err_syn(mini, "near unexpected token '|'"));
	}
	while (ongoing)
	{
		if (!(ongoing->next))
		{
			if (ongoing->operateur > 1 && ongoing->operateur < 6)
				return (err_syn(mini, "near unexpected token 'newline'"));
			return (0);
		}
		if (single_handle(mini, ongoing))
			return (1);
		else if (double_handle(mini, ongoing))
			return (1);
		ongoing = ongoing->next;
	}
	return (0);
}

int	weird_check(t_main *mini, char *str)
{
	if (!ft_strncmp(str, "!", 1))
		mini->shell.error = 1;
	else if (!ft_strncmp(str, ":", 1))
		mini->shell.error = 0;
	return (1);
}

int	check_all(t_main *mini)
{
	int		len;
	t_lexer	*tmp;

	tmp = mini->lexer_list;
	len = ft_size_list(mini->lexer_list);
	if (syntax_check(mini, len))
		return (1);
	if (var_check(mini, mini->lexer_list))
		return (1);
	while (tmp)
	{
		if (check_all_help(mini, tmp, len) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
