/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:31:12 by asalic            #+#    #+#             */
/*   Updated: 2023/10/13 17:12:41 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
