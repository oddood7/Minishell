/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:18:53 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 13:21:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    export_error_check(char *str)
{
    int        i;

    i = 0;
    while (str[i] == 32)
        i++;
    if (str[i] == '\0')
        return (err_exp(str, 1));
    if (ft_isdigit(str[0]) || check_identifier(str[0]))
        return (err_exp(str, 1));
    i = 0;
    while (str[i] != '=')
    {
        if (str[i] == '\0')
            break ;
        if (check_identifier(str[i]))
            return (err_exp(str, 1));
        i++;
    }
    return (0);
}

void    everything_add(t_main *mini, char *str)
{
    char    *str_quote;
    char    *str_check;
    int        i;

    i = 0;
    str_quote = malloc(sizeof(char) * ft_strlen(str) + 3);
    if (!str_quote)
        err_mall(mini);
    i = exp_var_quotes(str, str_quote);
    str_quote[i] = '\0';
    str_check = exp_var_name(mini, str);
    if (exist_in_env(mini, str_check) >= 0)
        remove_env_var(mini, exist_in_env(mini, str_check));
    if (exist_in_exp(mini, str_check) >= 0)
        remove_exp_var(mini, exist_in_exp(mini, str_check));
    var_to_env(mini, str);
    var_to_exp(mini, str_quote);
    free(str_quote);
    free(str_check);
}

void    export_support(t_main *mini, char *str)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            everything_add(mini, str);
            break ;
        }
        else if (str[i + 1] == '\0')
        {
            if ((exist_in_env(mini, str) >= 0))
                return ;
            else if (exist_in_exp(mini, str) >= 0)
                return ;
            var_to_exp(mini, str);
        }
        i++;
    }
    return ;
}

int    built_export(t_main *mini, t_parsing *cmd)
{
    int        i;

    i = 1;
    if (!cmd->cmd_tab[1] || cmd->cmd_tab[1][0] == '\0')
        return (print_env_exp(mini));
    while (cmd->cmd_tab[i])
    {
        if (export_error_check(cmd->cmd_tab[i]))
        {
            mini->shell.error = 1;
            return (1);
        }
        else
            export_support(mini, cmd->cmd_tab[i]);
        i++;
    }
    mini->shell.error = 0;
    return (1);
}
