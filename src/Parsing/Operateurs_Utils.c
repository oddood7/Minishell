/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operateurs_Utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:11:32 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/26 16:11:36 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	left_check(t_main *mini, t_lexer *ope)
{
	if (ope->next->operateur == RIGHT)
		return (err_syn(mini, "parse error near '\n'"));
	if (ope->next->operateur == LEFT && (!ope->next->next || ope->next->next->operateur != LEFT))
		return (err_syn(mini, "parse error near '<'"));
	if (ope->next->operateur == LEFT_LEFT)
	{
		if (!ope->next->next || (ope->next->next->operateur != LEFT && ope->next->next->operateur != LEFT_LEFT))
			return (err_syn(mini, "parse error near '<<'"));
		else if (ope->next->next && (ope->next->next->operateur == LEFT || ope->next->next->operateur == LEFT_LEFT))
			return (err_syn(mini, "parse error near '<<<'"));
	}
	if (ope->next->operateur == RIGHT_RIGHT)
	{
		if (!ope->next->next || (ope->next->next->operateur != RIGHT && ope->next->next->operateur != RIGHT_RIGHT))
			return (err_syn(mini, "parse error near '>'"));
		else if (ope->next->next->operateur == RIGHT || ope->next->next->operateur == RIGHT_RIGHT)
			return (err_syn(mini, "parse error near '>>'"));
	}
	return (0);
}	

int    right_check(t_main *mini, t_lexer *ope)
{
    if (ope->next->operateur == LEFT)
        return (err_syn(mini, "parse error near `<'"));
    if (ope->next->operateur == RIGHT)
        return (err_syn(mini, "parse error near `>'"));
    if (ope->next->operateur == RIGHT_RIGHT)
        return (err_syn(mini, "parse error near `>>'"));
    if (ope->next->operateur == LEFT_LEFT)
    {
        if (ope->next->next || (ope->next->next->operateur != LEFT &&(ope->next->next->operateur != LEFT_LEFT)))
            return (err_syn(mini, "parse error near `<<'"));
        else if (ope->next->next->operateur == LEFT ||(ope->next->next->operateur == LEFT_LEFT))
            return (err_syn(mini, "parse error near `<<<'"));
    }
    return (0);
}

int	pipe_check(t_main *mini, t_lexer *ope)
{
	if (ope->next->operateur == PIPE)
	{
		if (!ope->next->next)
			return (err_syn(mini, "parse error near '\n"));
		if (ope->next->next->operateur == PIPE)
		{
			if (ope->next->next->next && ope->next->next->next->operateur == PIPE)
				return (err_syn(mini, "parse error near ||"));
			else
				return (err_syn(mini, "parse error near |"));
		}
	}
	return (0);
}

int    left2_check(t_main *data, t_lexer *ope)
{
    if (ope->next->operateur == PIPE)
    {
        if (ope->next->next && ope->next->next->operateur == PIPE)
            return (err_syn(data, "parse error near `||'"));
        else
            return (err_syn(data, "parse error near `|'"));
    }
    else if (ope->next->operateur == LEFT_LEFT)
    {
        if (!ope->next->next || (ope->next->next->operateur != LEFT
                && ope->next->next->operateur != LEFT_LEFT))
            return (err_syn(data, "parse error near `<'"));
        else if (ope->next->next->operateur == LEFT)
            return (err_syn(data, "parse error near `<<'"));
        else if (ope->next->next->operateur == LEFT_LEFT)
            return (err_syn(data, "parse error near `<<<'"));
    }
    return (0);
}

int    right2_check(t_main *data, t_lexer *ope)
{
    if (ope->next->operateur == PIPE)
    {
        if (ope->next->next && ope->next->next->operateur == PIPE)
            return (err_syn(data, "parse error near `||'"));
        else
            return (err_syn(data, "parse error near `|'"));
    }
    if (ope->next->operateur == RIGHT)
        return (err_syn(data, "parse error near `>'"));
    if (ope->next->operateur == RIGHT_RIGHT)
        return (err_syn(data, "parse error near `>>'"));
    return (0);
}