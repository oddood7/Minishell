/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/16 17:32:43 by asalic           ###   ########.fr       */
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
	tmp = ft_malloc(sizeof(char) * i + 1);
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

char    *just_alloc(int len, int j_dol, char *s_af)
{
    char    *ok;

    if (s_af)
        ok = ft_malloc(sizeof(char) * (j_dol + len + ft_strlen(s_af)) + 1);
    else
        ok = ft_malloc(sizeof(char) * (j_dol + len) + 1);
    if (!ok)
        return (NULL);
    return (ok);
}

int	util_free_expand(char *str, char *tmp)
{
	(void)(str);
	(void)(tmp);
	//free(str);
	//free(tmp);
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
    //free(tmp);
    return ;
}

/* Compte nombre de maillon dans une liste */
int	len_targs(t_lexer *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len ++;
		list = list->next;
	}
	return (len);
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

char	**env_to_char(t_lexer **env_list)
{
	t_lexer	*current;
	char	**env_char;
	int		i;

	current = *env_list;
	env_char = ft_malloc(len_targs(current) * (sizeof * current));
	if (!env_char)
		return (NULL);
	i = 0;
	while (current)
	{
		env_char[i] = ft_strdup(current->str);
		if (!env_char[i])
		{
			while (i >= 0)
				//free(env_char[i--]);
			//free(env_char);
			return (NULL);
		}			
		current = current->next;
		i ++;
	}
	env_char[i] = NULL;
	return (env_char);
}
