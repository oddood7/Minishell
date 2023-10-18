/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/18 13:03:41 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
