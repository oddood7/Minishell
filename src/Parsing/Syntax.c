/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:07:53 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 01:41:05 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	slash_manage(t_main *mini, char *str)
{
	int i;

	i = 0;
	if (str[i] == '/')
	{
		i++;
		while (str[i] == '/')
			i++;
		if (str[i] == '\0')
			return (directory_err(mini, str, 0));
		if (!access(str, F_OK))
			return (0);
		else
			return (directory_err(mini, str, 1));
	}
	if (str[i] == '.' && str[i + 1] == '/')
	{
		i++;
		while (str[i] == '/')
			i++;
		if (str[i] == '\0')
			return (directory_err(mini, str, 0));
	}
	return (0);
}

int	string_syn(t_main *mini, char *str)
{
	int        i;

    i = 0;
    if (is_rchar(str[0], '\'') || is_rchar(str[0], '"'))
        return (0);
    while (str[i])
    {
        if (is_rchar(str[i], '&'))
        {
            if (is_rchar(str[i + 1], '&'))
                return (err_syn(mini, "near unexpected token`&&'"));
            return (err_syn(mini, "near unexpected token`&'"));
        }
        else if (is_rchar(str[i], ';'))
        {
            if (is_rchar(str[i + 1], ';'))
                return (err_syn(mini, "near unexpected token`;;'"));
            return (err_syn(mini, "near unexpected token`;'"));
        }
        else if (string_syn_plus(mini, str, i))
            return (1);
        i++;
    }
    return (0);
}
int	string_syn_plus(t_main *mini, char *str, int i)
{	
	if (is_rchar(str[i], ')'))
        return (err_syn(mini, "near unexpected token `)'"));
    else if (is_rchar(str[i], '\\'))
        return (err_syn(mini, "near unexpected token `\\'"));
    else if (is_rchar(str[i], '('))
        return (err_syn(mini, "should close parentheses"));
    return (0);
}

int    string_syn2(t_main *mini, t_lexer *ongoing)
{
    if (ongoing->next && ongoing->next->str)
    {
        if (slash_manage(mini, ongoing->next->str))
            return (1);
    }
    else if (ongoing->next && ongoing->next->operateur)
    {
        if (two_pipes(mini, ongoing))
            return (1);
    }
    return (0);
}

int    syntax_check(t_main *mini, int size)
{
    t_lexer    *ongoing;

    (void)size;
    ongoing = mini->lexer_list;
    if (ongoing->str)
    {
        if (slash_manage(mini, ongoing->str))
            return (1);
    }
    while (ongoing)
    {
        if (ongoing->operateur)
        {
            if (string_syn2(mini, ongoing))
                return (1);
        }
        else if (ongoing->str)
            if (string_syn(mini, ongoing->str))
                return (1);
        ongoing = ongoing->next;
    }
    return (0);
}