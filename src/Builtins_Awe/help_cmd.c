/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:12:28 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 18:40:26 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/*
 * Ajout nouveau maillon dans env.
 * Boucle jusqu'a la fin de la liste.
 * Puis ajoute la string.
 * (BUG: sauf qu'il l'ajoute de maniere random ou il veut dans l'env ;-;)
*/
void	add_env(t_lexer **env_list, char *str)
{
	t_lexer	*new_var;
	t_lexer	*current;

	new_var = ft_calloc(1, sizeof *new_var);
	if (! new_var)	
		return ;
	new_var->str = ft_strdup(str);
	if (! new_var->str)
	{
		free(new_var);
		return ;
	}
	// new_var->token = 0;
	new_var->next = NULL;
	if (*env_list)
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = copy_list(new_var);
	}
	else
		*env_list = copy_list(new_var);
	free(new_var);
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

/* Dupplique un (char **) */
char	**dup_double_string(t_lexer **e_list)
{
	char	**result;
	t_lexer	*current;
	int		len_args;
	int		i;

	i = 0;
	current = *e_list;
	len_args = len_targs(current);
	result = ft_calloc(len_args + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (current)
	{
		result[i] = ft_strdup(current->str);
		if (result[i] == NULL)
		{
			while (i >= 0)
				free(result[i--]);
			return (NULL);
		}
		i ++;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

/* 
 * Permets de copier un liste d'args
*/
t_lexer *copy_list(t_lexer *source)
{
    t_lexer* new_head;
    t_lexer* current;
    t_lexer* tail;

	new_head = NULL;
	tail = NULL;
	current = source;
    while (current != NULL)
	{
        if (new_head == NULL)
		{
            new_head = ft_calloc(1, sizeof(t_lexer));
            new_head->str = current->str;
            new_head->next = NULL;
            tail = new_head;
        }
		else
		{
            tail->next = ft_calloc(1, sizeof(t_lexer));
            tail = tail->next;
            tail->str = current->str;
        }
        current = current->next;
    }
	free(tail->next);
    return (new_head);
}
