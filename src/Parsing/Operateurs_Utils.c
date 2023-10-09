/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operateurs_Utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:11:32 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	left_check(t_main *mini, t_lexer *ope)
{
	if (ope->next->operateur == RIGHT)
		return (err_syn(mini, "near unexpected token '\n'"));
	if (ope->next->operateur == LEFT && (!ope->next->next || ope->next->next->operateur != LEFT))
		return (err_syn(mini, "near unexpected token '<'"));
	if (ope->next->operateur == LEFT_LEFT)
	{
		if (!ope->next->next || (ope->next->next->operateur != LEFT && ope->next->next->operateur != LEFT_LEFT))
			return (err_syn(mini, "near unexpected token '<<'"));
		else if (ope->next->next && (ope->next->next->operateur == LEFT || ope->next->next->operateur == LEFT_LEFT))
			return (err_syn(mini, "near unexpected token '<<<'"));
	}
	if (ope->next->operateur == RIGHT_RIGHT)
	{
		if (!ope->next->next || (ope->next->next->operateur != RIGHT && ope->next->next->operateur != RIGHT_RIGHT))
			return (err_syn(mini, "near unexpected token '>'"));
		else if (ope->next->next->operateur == RIGHT || ope->next->next->operateur == RIGHT_RIGHT)
			return (err_syn(mini, "near unexpected token '>>'"));
	}
	return (0);
}	

int    right_check(t_main *mini, t_lexer *ope)
{
    if (ope->next->operateur == LEFT)
        return (err_syn(mini, "near unexpected token `<'"));
    if (ope->next->operateur == RIGHT)
        return (err_syn(mini, "near unexpected token `>'"));
    if (ope->next->operateur == RIGHT_RIGHT)
        return (err_syn(mini, "near unexpected token `>>'"));
    if (ope->next->operateur == LEFT_LEFT)
    {
        if (ope->next->next || (ope->next->next->operateur != LEFT &&(ope->next->next->operateur != LEFT_LEFT)))
            return (err_syn(mini, "near unexpected token `<<'"));
        else if (ope->next->next->operateur == LEFT ||(ope->next->next->operateur == LEFT_LEFT))
            return (err_syn(mini, "near unexpected token `<<<'"));
    }
    return (0);
}

int	pipe_check(t_main *mini, t_lexer *ope)
{
	if (ope->next->operateur == PIPE)
	{
		if (!ope->next->next)
			return (err_syn(mini, "near unexpected token '\n"));
		if (ope->next->next->operateur == PIPE)
		{
			if (ope->next->next->next && ope->next->next->next->operateur == PIPE)
				return (err_syn(mini, "near unexpected token ||"));
			else
				return (err_syn(mini, "near unexpected token |"));
		}
	}
	return (0);
}

int    left2_check(t_main *data, t_lexer *ope)
{
    if (ope->next->operateur == PIPE)
    {
        if (ope->next->next && ope->next->next->operateur == PIPE)
            return (err_syn(data, "near unexpected token `||'"));
        else
            return (err_syn(data, "near unexpected token `|'"));
    }
    else if (ope->next->operateur == LEFT_LEFT)
    {
        if (!ope->next->next || (ope->next->next->operateur != LEFT
                && ope->next->next->operateur != LEFT_LEFT))
            return (err_syn(data, "near unexpected token `<'"));
        else if (ope->next->next->operateur == LEFT)
            return (err_syn(data, "near unexpected token `<<'"));
        else if (ope->next->next->operateur == LEFT_LEFT)
            return (err_syn(data, "near unexpected token `<<<'"));
    }
    return (0);
}

int    right2_check(t_main *data, t_lexer *ope)
{
    if (ope->next->operateur == PIPE)
    {
        if (ope->next->next && ope->next->next->operateur == PIPE)
            return (err_syn(data, "near unexpected token `||'"));
        else
            return (err_syn(data, "near unexpected token `|'"));
    }
    if (ope->next->operateur == RIGHT)
        return (err_syn(data, "near unexpected token `>'"));
    if (ope->next->operateur == RIGHT_RIGHT)
        return (err_syn(data, "near unexpected token `>>'"));
    return (0);
}