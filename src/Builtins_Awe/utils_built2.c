/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:31:12 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 16:26:11 by asalic           ###   ########.fr       */
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

	new_var = ft_malloc(sizeof *new_var);
	new_var->str = str;
	new_var->next = NULL;
	if (*env_list)
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_var;
	}
	else
		*env_list = new_var;
}

// /* 
//  * Permets de copier un liste d'args
// */
// t_lexer *copy_list(t_lexer *source)
// {
//     t_lexer* new_head;
//     t_lexer* current;
//     t_lexer* tail;

// 	new_head = NULL;
// 	tail = NULL;
// 	current = source;
//     while (current != NULL)
// 	{
//         if (new_head == NULL)
// 		{
//             new_head = ft_malloc(sizeof(t_lexer));
//             new_head->str = current->str;
//             new_head->next = NULL;
//             tail = new_head;
//         }
// 		else
// 		{
//             tail->next = ft_malloc(sizeof(t_lexer));
//             tail = tail->next;
//             tail->str = current->str;
//         }
//         current = current->next;
//     }
//     return (new_head);
// }

/*
 * Gere export sans args
 * Affiche: declare -x VE env
*/
int	export_out_main(t_main *mini)
{
	char	*bfore;
	char	*after;
	char	**env_sort;
	int		i;

	bfore = NULL;
	after = NULL;
	env_sort = ft_sort(&mini->env_list);
	i = 0;
	while (env_sort[i])
	{
		bfore = ft_strdupto_n(env_sort[i], '=');
		after = ft_strdup_from(env_sort[i], '=');
		if (ft_strncmp(bfore, "?=", 2) == 0)
			i ++;
		else
			ft_printf("declare -x %s=\"%s\"\n", bfore, after);
		i ++;
	}
	mini->shell.error = handle_error_bis(0);
	return (0);
}

/* 
 * Mini parsing des args d'export
 * Check si le nom est conforme, juste des chiffres, des lettres et des
 * underscores
*/
int	parse_export(char *str)
{
	int	i;

	i = 0;
	if (!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a'
			&& str[0] <= 'z'))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] \
			>= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' \
			&& str[i] <= 'z') && str[i] != '_')
			return (1);
		i ++;
	}
	if (str[i] == '=')
		return (0);
	return (2);
}
