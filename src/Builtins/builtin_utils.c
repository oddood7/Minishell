/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:41:36 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *copy_pwd(t_main *mini, char *s, int i)
{
    int        j;
    int        k;
    char    *old;

    j = 4;
    k = 0;
    while (mini->env[i][j])
        s[k++] = mini->env[i][j++];
    s[k] = '\0';
    old = ft_strjoin("OLDPWD=", s);
    free(s);
    return (old);
}

char    *copy_declarex(t_main *mini, char *s, int i)
{
    int        j;
    int        k;
    char    *ok;

    j = 15;
    k = 0;
    while (mini->env_exp[i][j])
        s[k++] = mini->env_exp[i][j++];
    s[k] = '\0';
    ok = ft_strjoin("declare -x OLDPWD=", s);
    free(s);
    return (ok);
}

char    *add_quote(t_main *mini, char *s)
{
    int        i;
    int        j;
    char    *tmp;
    char    *ok;

    i = 0;
    j = 0;
    tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
    if (!tmp)
        err_mall(mini);
    while (s[i])
        tmp[j++] = s[i++];
    tmp[j] = '\0';
    i = 0;
    j = 1;
    s[0] = '\"';
    while (tmp[i])
        s[j++] = tmp[i++];
    s[j++] = '\"';
    s[j] = '\0';
    ok = ft_strjoin("declare -x PWD=", s);
    free(tmp);
    return (ok);
}