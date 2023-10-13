/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cmd_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:42:25 by asalic            #+#    #+#             */
/*   Updated: 2023/10/13 16:36:07 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Fonction d'extension de cd.
 * Permets de mettre a jour ou d'export pwd et oldpwd lorsque cd change
 * de repertoire.
*/
int	cd_move_and_change(t_main *mini)
{
	char	*old_pwd_change;
	char	*old_cmd;
	char	*current_cmd;
	char	*new_pwd;
	char	*tmp;

	old_pwd_change = ft_strjoin("OLDPWD=", mini->shell.is_pwd);
	if (!old_pwd_change)
		return (1);
	old_cmd = ft_strjoin("OLDPWD=", mini->shell.is_oldpwd);
	if (!old_cmd)
	{
		free(old_pwd_change);
		return (1);
	}
	change_env_cd(&mini->env_list, old_pwd_change, old_cmd);
	free(old_cmd);
	free(old_pwd_change);
	free(mini->shell.is_oldpwd);
	free(mini->shell.oldpwd);
	mini->shell.is_oldpwd = ft_strdup(mini->shell.is_pwd);
	mini->shell.oldpwd = ft_strdup(mini->shell.is_pwd);
	tmp = getcwd(NULL, 0);
	current_cmd = ft_strdup(tmp);
	free(tmp);
	if (current_cmd != NULL)
	{
		new_pwd = ft_strjoin("PWD=", current_cmd);
		if (!new_pwd)
		{
			free(current_cmd);
			return (1);
		}
		old_cmd = ft_strjoin("PWD=", mini->shell.is_pwd);
		if (!old_cmd)
		{
			free(current_cmd);
			free(new_pwd);
			return (1);
		}
		change_env_cd(&mini->env_list, new_pwd, old_cmd);
		free(mini->shell.pwd);
		free(mini->shell.is_pwd);
		mini->shell.is_pwd = ft_strdup(current_cmd);
		mini->shell.pwd = ft_strdup(current_cmd);
		free(current_cmd);
		free(new_pwd);
		free(old_cmd);
	}
	else
		return (1);
	mini->env = env_to_char(&mini->env_list);
	return (0);
}

static int	nbcount(long long int n)
{
	long long int	nbr;
	long int		nb;

	nbr = n;
	nb = 1;
	if (n < 0)
	{
		nb++;
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		nb++;
	}
	return (nb);
}

char	*ft_long_itoa(long long int n)
{
	long long int		nbr;
	char				*str;
	long long int		i;

	str = malloc(sizeof(char) * (nbcount(n) + 1));
	if (!str)
		return (NULL);
	str[nbcount(n)] = '\0';
	i = nbcount(n) - 1;
	nbr = n;
	if (n < 0)
	{
		str[0] = '-';
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	str[i] = nbr + '0';
	return (str);
}

long long int	ft_long_atoi(const char *nptr)
{
	long long int	i;
	long long int	res;
	long long int	c;

	i = 0;
	c = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			c = c * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * c);
}