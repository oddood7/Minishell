/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:00:28 by lde-mais          #+#    #+#             */
/*   ngldated: 2023/09/22 21:06:11 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    add_w_dig(char *str, int i, int j)
{
    while (str[i + j] && !is_ope(str[i + j]))
    {
        if (str[i + j] == 34)
        {
            j++;
            while (str[i + j] != 34 && str[i + j])
                j++;
            j++;
            break ;
        }
        else if (str[i + j] == 39)
        {
            j++;
            while (str[i + j] != 39 && str[i + j])
                j++;
            j++;
            break ;
        }
        else
            j++;
    }
    return (j);
}

int	get_word_quote(char *str, int i, int j, int quote)
{
    j++;
    while (str[i + j] != quote && str[i + j])
    {
        j++;
        if (str[i + j] == quote && str[i + j + 1] == quote)
            j = (add_w_dig(str, i, j++));
        else if (str[i + j] == quote)
            return (j + 1);
    }
    j++;
    return (j);
}

int    get_to_quote(char *str, int i)
{
    int    j;

    j = 0;
    while (str[i + j] && !is_ope(str[i + j]) && str[i + j] != ' ')
    {
        if (str[i + j] == 34)
        {
            j += get_word_quote(str, i, j, 34);
            if (str[i + j] == ' ')
                break ;
        }
        else if (str[i + j] == 39)
        {
            j += get_word_quote(str, i, j, 39);
            if (str[i + j] == 32)
                break ;
        }
        else
            j++;
    }
    return (j);
}

int    different_get_to_quote(char *str, int i, int j)
{
    if (!str[i])
        return (0);
	printf("Starting i: %d, j: %d\n", i, j);
    while (((i + j) < (int)ft_strlen(str) + 1) && !is_ope(str[i + j])
        && str[i + j] != ' ')
    {
		j++;
		/* if (is_ope(str[i + j]) || str[i + j] == ' ')
        	break; */
        if (str[i + j] == 34 && str[i + j + 1] != 34)
        {
            j++;
            while (str[i + j] && str[i + j] != 34)
                j++;
            if (str[i + j] == 34 && str[i + j + 1] == ' ')
                return (j + 1);
        }                
        else if (str[i + j] == 39 && str[i + j + 1] != 39)
        {
            j++;
            while (str[i + j] && str[i + j] != 39)
                j++;
            if (str[i + j] == 39 && str[i + j + 1] == ' ')
                return (j + 1);
        }                                        
        j++;
    }
	printf("Ending i: %d, j: %d\n", i, j);
    return (j);
}

int    count_single_quote(char *str, int i)
{
    int    single;

    single = 0;
    while (str[i])
    {
        if (str[i] == ' ' && !single)
            return (0);
        if (str[i] == 39)
        {
            if (str[i + 1] == 39)
                return (0);
            single++;
        }
        i++;
    }
    return (single);
}

int    count_double_quote(char *str, int i)
{
    int    doubl;

    doubl = 0;
    while (str[i])
    {
        if (str[i] == ' ' && !doubl)
            return (0);
        if (str[i] == 34)
        {
            if (str[i + 1] == 34)
                return (0);
            else
                doubl++;
        }
        i++;
    }
    return (doubl);
}