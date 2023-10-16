/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:03:26 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/16 17:04:22 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Recupere str jusqu'a c.
 * Creation d'un tableau a partir de str jusqu'a atteindre le caractere c.
 * Compter d'abord le nombre de caractere a ajouter a tab.
 * Puis, ajout a tab.
*/
char	*ft_strdupto_n(char *str, char c)
{
	char	*tab;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != c)
	{
		len ++;
		i ++;
	}
	tab = ft_calloc((len +1), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		tab[i] = str[i];
		i ++;
	}
	tab[i] = '\0';
	return (tab);
}

/* 
 * Recupere str a partir de c.
*/
char	*ft_strdup_from(char *str, char c)
{
	char	*tab;
	int		i;
	int		start;
	int		len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != c)
		i ++;
	if (str[i] == c)
		i ++;
	start = i;
	while (str[i++])
		len ++;
	tab = ft_calloc((len +1), sizeof(char));
	if (!tab)
		return (NULL);
	i = start;
	len = 0;
	while (str[i])
		tab[len++] = str[i++];
	tab[len] = '\0';
	return (tab);
}

/* 
 * Part de la fin de str et recule jusqu'a c.
 * Puis copie du debut de la chaine jusqu'a ce c marque
*/
char	*from_end_to_char(char *str, char c)
{
	int		i;
	int		max;
	char	*tab;

	i = ft_strlen(str) -1;
	while (i >= 0 && str[i] != c)
		i --;
	max = i;
	tab = ft_calloc((max +1), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < max)
	{
		tab[i] = str[i];
		i ++;
	}
	tab[i] = '\0';
	return (tab);
}

char    **ft_sort(t_lexer **env_list)
{
    int			i;
    char		*temp;
	char		**env_char;
    int			must_continue;

	env_char = env_to_char(env_list);
    must_continue = 1;
    while (must_continue)
    {
        must_continue = 0;
        i = 1;
        while (env_char[i + 1])
        {
            if (ft_strncmp(env_char[i], env_char[i + 1],
                    ft_strlen(env_char[i]) + ft_strlen(env_char[i + 1])) > 0)
            {
                temp = env_char[i];
                env_char[i] = env_char[i + 1];
                env_char[i + 1] = temp;
                must_continue = 1;
            }
            i++;
        }
    }
	env_char[i] = NULL;
	return (env_char);
}
