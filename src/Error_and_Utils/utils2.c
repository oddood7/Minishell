/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:59:06 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_name(char *str, t_main *mini)
{
	char	*tmp;
	int		i;

	i = 0;
	(void) mini;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	tmp = ft_malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*just_alloc(int len, int j_dol, char *s_af)
{
	char	*ok;

	if (s_af)
		ok = ft_malloc(sizeof(char) * (j_dol + len + ft_strlen(s_af)) + 1);
	else
		ok = ft_malloc(sizeof(char) * (j_dol + len) + 1);
	if (!ok)
		return (NULL);
	return (ok);
}

void	print_no_command(t_main *mini, char *s, int i)
{
	int		ok;
	char	*tmp;

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
	return ;
}

/* 
 * Strlen pour un char **.
*/
int	ft_strlen_double(char **str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str ++;
		i ++;
	}
	return (i);
}

/*
 * Check si la chaine de caractere est bien remplie de nombre
 * Que des caracteres numeriques
*/
int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i ++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
