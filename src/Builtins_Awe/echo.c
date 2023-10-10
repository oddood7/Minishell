/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:37:52 by asalic            #+#    #+#             */
/*   Updated: 2023/10/10 12:55:03 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Cherche s2 dans s1.
 * Parcours s1 jusqu'a trouver s2 a la suite.
*/
static int	find_opt(char *s1)
{
	size_t	i;

	i = 1;
	if (s1[0] != '-')
		return (0);
	while (s1[i] && s1[i] == 'n')
	{
		i ++;
		if (!s1[i])
			return (1);
	}
	return (0);
}

/* 
 * Affiche caractere par caractere la liste.
 * Suite de ft_echo.
*/
static int	iter_echo(char	*str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		write (1, &str[i], 1);
		i ++;
	}
	return (0);
}

static void	echo_loop(char **cmd_tab, int i, t_shell *shell)
{
	if (ft_strcmp("$?", cmd_tab[i]) == 0 && ft_strlen(cmd_tab[i]) == 2)
		printf("%d", shell->error);
	else
	{
		while (cmd_tab[i])
		{
			if (iter_echo(cmd_tab[i]) == 0 && cmd_tab[i + 1] != NULL)
				write (1, " ", 1);
			i ++;
		}
	}
}

/*
 * Fonction a l'image de 'echo'.
 * Affiche caractere par caractere les arguments en ignorant les quotes.
 * (Attention: cas particuliers, quotes a l'interieur de d'autres).
*/
int	ft_echo(t_main *mini, t_parsing *parse)
{
	int	bools;
	int	i;

	bools = 0;
	i = 1;
	if (!parse->cmd_tab[i])
	{
		write (1, "\n", 1);
		return (1);
	}
	while (parse->cmd_tab[i] && ft_strcmp(parse->cmd_tab[i], "\t") == 0)
		i ++;
	while (parse->cmd_tab[i] && find_opt(parse->cmd_tab[i]) == 1)
	{
		i ++;
		bools = 1;
	}
	echo_loop(parse->cmd_tab, i, &mini->shell);
	if (bools == 0)
		write (1, "\n", 1);
	if (change_error(&mini->env_list, &mini->shell, 0) == 1)
		return (1);
	return (0);
}
