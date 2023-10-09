/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
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

char    *just_alloc(int len, int j_dol, char *s_af)
{
    char    *ok;

    if (s_af)
        ok = malloc(sizeof(char) * (j_dol + len + ft_strlen(s_af)) + 1);
    else
        ok = malloc(sizeof(char) * (j_dol + len) + 1);
    if (!ok)
        return (NULL);
    return (ok);
}

int	util_free_expand(char *str, char *tmp)
{
	free(str);
	free(tmp);
	return (0);
}

void    print_no_command(t_main *mini, char *s, int i)
{
    int        ok;
    char    *tmp;

    ok = 0;
    if (s == NULL)
    {
        ft_putendl_fd(": command not found", 2);
        return ;
    }
    while (mini->env[i])
    {
        if (!ft_strncmp(mini->env[i++], "PATH=", 5))
            ok = 1;
    }
    if (ok)
    {
        write(2, s, ft_strlen(s));
        ft_putendl_fd(": command not found", 2);
        return ;
    }
    tmp = ft_strjoin(s, ": No such file or directory\n");
    write(2, tmp, ft_strlen(tmp));
    free(tmp);
    return ;
}