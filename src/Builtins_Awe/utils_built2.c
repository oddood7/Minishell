/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:31:12 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 18:38:13 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Compte le nombre de directory qui n'existe plus depuis rm -rf.
 * Ignore les /..
*/
int	count_dir(t_shell *shell)
{
	int		len;
	char	*temp;
	DIR		*dir;

	len = 0;
	temp = shell->is_pwd;
	dir = opendir(temp);
	while (!dir)
	{
		if (temp[ft_strlen(temp) - 1] != '.' && temp[ft_strlen(temp) - 2] \
			!= '.' && temp[ft_strlen(temp) - 3] != '/')
			len ++;
		temp = from_end_to_char(temp, '/');
		closedir(dir);
		dir = opendir(temp);
	}
	closedir(dir);
	return (len -1);
}

/*
 * Compte le nombre de /.. apres les directory.
*/
int	count_back(char	*str)
{
	int		len;
	int		i;
	char	**tab;

	tab = ft_split(str, '/');
	i = ft_strlen_double(tab) - 1;
	len = 0;
	while (i >= 0)
	{
		if (ft_strncmp(tab[i], "..", ft_strlen(tab[i])) == 0)
			len ++;
		else
			return (len);
		i --;
	}
	return (len);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	l = ft_strlen(s1) + ft_strlen(s2);
	new = ft_calloc(l + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (free(s1), free(s2), new);
}

static char	**env_to_char(t_lexer **env_list)
{
	t_lexer	*current;
	char	**env_char;
	int		i;

	current = *env_list;
	env_char = ft_calloc(len_targs(current), sizeof *current);
	if (!env_char)
		return (NULL);
	i = 0;
	while (current)
	{
		env_char[i] = ft_strdup(current->str);
		if (!env_char[i])
		{
			while (i >= 0)
				free(env_char[i--]);
			free(env_char);
		}			
		current = current->next;
		i ++;
	}
	env_char[i] = NULL;
	return (env_char);
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
