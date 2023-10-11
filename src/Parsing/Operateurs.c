/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operateurs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:11:52 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 16:19:51 by asalic           ###   ########.fr       */
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
				return(err_syn(mini, "near unexpected token '||'"));
			else
				return(err_syn(mini, "near unexpected token '|'"));
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
	t_lexer *ongoing;

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
				return (err_syn(mini, "near unexpected token '\n'"));
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

int weird_check(t_main *mini, char *str)
{
	if (!ft_strncmp(str, "!", 1))
		mini->shell.error = 1;
	else if (!ft_strncmp(str, ":", 1))
		mini->shell.error = 0;
	return (1);
}

int check_all(t_main *mini)
{
	int len;
	t_lexer *tmp;

	tmp = mini->lexer_list;
	len = ft_size_list(mini->lexer_list);
	if (syntax_check(mini, len))
		return (1);
	if (var_check(mini, mini->lexer_list))
		return (1);
	while (tmp)
	{
		if (len == 1 && !tmp->operateur)
		{
			if ((!ft_strncmp(tmp->str, "!", 1) || !ft_strncmp(tmp->str, ":", 1)) && ft_strlen(tmp->str) == 1)
				return (weird_check(mini, tmp->str));
			else if (!ft_strncmp(tmp->str, ".", 1) && ft_strlen(tmp->str) == 1)
			{
				mini->shell.error = handle_error_bis(2);
				return (mini->shell.error);
			}
			else if (!ft_strncmp(tmp->str, "..", 2) && ft_strlen(tmp->str) == 2)
			{
				mini->shell.error = handle_error_bis(127);
				return (mini->shell.error);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}