/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/05 16:45:37 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*get_var_name(char *str, t_main *mini)
{
	char *tmp;
	int i;

	i = 0;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		err_mall(mini);
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int    arg_check(t_main *mini, char **tab)
{
    int    i;

    i = 0;
    while (tab[i])
        i++;
    if (i > 2)
    {
        ft_putendl_fd("bash: cd: too many arguments", 2);
        mini->return_value = 1;
        return (1);
    }
    return (0);
}