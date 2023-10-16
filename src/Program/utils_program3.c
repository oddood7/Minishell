/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_program3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:34:21 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/16 15:45:21 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    check_space(char *str)
{
    int    i;

    i = 0;
    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (0);
    else
        return (1);
}

int    error_quote2(t_main *mini, char *str, int sep)
{
    int    ok;
    int    comp;

    ok = 0;
    comp = 0;
    while (str[ok])
    {
        if (str[ok++] == sep)
            comp++;
    }
    if (comp % 2 == 0)
        return (0);
    else
    {
        mini->shell.error = handle_error_bis(2);
        return (mini->shell.error);
    }
}

int    error_quote(t_main *mini, char *str, int sep1, int sep2)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (str[i] == sep1)
            return (error_quote2(mini, str, sep1));
        else if (str[i] == sep2)
            return (error_quote2(mini, str, sep2));
        i++;
    }
    return (0);
}

void	init_main(t_main *mini)
{
    mini->env = NULL;
	mini->lexer_list = NULL;
    mini->env_list = NULL;
	mini->cmd_parse = NULL;
	mini->shell.error = 0;
	mini->syntaxe_check = 0;
    ft_bzero(&mini->shell, sizeof(t_shell));
    mini->shell.input_bis = NULL;
	sig_init();
}

int main_space(char *str)
{
	ft_putendl_fd(str, 1);
	return (1);
}