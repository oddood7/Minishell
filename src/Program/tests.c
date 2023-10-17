/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:23:54 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 17:21:07 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../../include/minishell.h"

void    pr(t_lexer *lexer_list)
{
    t_lexer    *tmp;
    int        i;

    i = 0;
    fprintf(stderr, "[CHECK LEXER] ");
    if (!lexer_list)
    {
        fprintf(stderr, "lexer_list is clean\n");
        return ;
    }
    tmp = lexer_list;
    while (tmp)
    {
        fprintf(stderr, "[node %d: ", i);
        if (tmp->str)
            fprintf(stderr, "(%s)]", tmp->str);
        else
            fprintf(stderr, "%d]", tmp->i);
        i++;
        tmp = tmp->next;
    }
    fprintf(stderr, "\n");
}

void    pr_redir(t_lexer *lexer_list)
{
    t_lexer        *tmp;
    int            i;

    i = 0;
    fprintf(stderr, "[CHECK REDIR]");
    if (!lexer_list)
    {
        fprintf(stderr, "no redir list\n");
        return ;
    }
    tmp = lexer_list;
    while (tmp)
    {
        fprintf(stderr, " | node %d: ", i);
        if (tmp->str)
            fprintf(stderr, "file=[%s] ", tmp->str);
        if (tmp->operateur)
        tmp = tmp->next;
        i++;
    }
    fprintf(stderr, "\n");
}

void    prrr(t_parsing *cmd_parse, int ok)
{
    t_parsing    *tmp;
    int            i;

    tmp = cmd_parse;
    fprintf(stderr, "[FINAL LIST]");
    if (ok == 1)
        fprintf(stderr, " before expander :");
    else
        fprintf(stderr, " after expander :");
    while (tmp)
    {
        i = 0;
        fprintf(stderr, " | new node->cmd_tab = ");
        while (tmp->cmd_tab[i])
        {
            fprintf(stderr, "[%s]", tmp->cmd_tab[i]);
            i++;
        }
        tmp = tmp->next;
    }
    fprintf(stderr, "\n");
} */