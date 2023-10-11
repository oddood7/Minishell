/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:34:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 16:22:05 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    dir_file_check(t_main *mini, char *str)
{
    int    i;

    i = 0;
    if (str[i] == '.' && str[i + 1] == '/')
    {
        if (opendir(str + 2))
        {
            mini->shell.error = 126;
            return (ft_perror(str));
        }
        else if (access(str + 2, F_OK))
        {
            mini->shell.error = 127;
            perror(str);
            return (1);
        }
        mini->shell.error = 0;
    }
    return (0);
}

int    finding_var(t_main *mini, char *str, int len)
{
    int    i;

    i = 0;
    while (mini->env[i])
    {
        if (!ft_strncmp(str + 1, mini->env[i], len - 1)
            && mini->env[i][len - 1] == '=')
            return (1);
        i++;
    }
    return (0);
}

int    var_check(t_main *mini, t_lexer *list)
{
    int    len;

    if (ft_size_list(list) == 1)
    {
        if (list->str)
        {
            len = ft_strlen(list->str);
            if (list->str[0] == '$')
            {
                if (len == 1)
                {
                    mini->shell.error = handle_error_bis(127);
                    return (mini->shell.error);
                }
                if (!ft_strncmp(list->str + 1, "?", 1) && len == 2)
                    return (0);
                if (!ft_strncmp(list->str + 1, "PWD", 3) && len == 4)
                    return (directory_err(mini, "$PWD", 0));
                if (!ft_strncmp(list->str + 1, "OLDPWD", 3) && len == 7)
                    return (directory_err(mini, "$OLDPWD", 0));
                else if (!finding_var(mini, list->str, len))
                    return (1);
            }
            return (dir_file_check(mini, list->str));
        }
    }
    return (0);
}