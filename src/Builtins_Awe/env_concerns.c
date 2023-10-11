/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_concerns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:59:01 by asalic            #+#    #+#             */
/*   Updated: 2023/10/11 16:11:04 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Modif de l'env pour cd
 * Parcourt env_list jusqu'a l'element que l'on veut changer.
 * Puis, modifier cette valeur avec new_str
*/
void	change_env_cd(t_lexer **env_list, char *new_str, char *change_value)
{
	t_lexer	*current;

	current = *env_list;
	while (current && current->str != NULL)
	{
		if (ft_strcmp(current->str, change_value) == 0 && \
			ft_strlen(current->str) == ft_strlen(change_value))
		{
			if (current->str)
				free(current->str);
			current->str = ft_strdup(new_str);
			return ;
		}
		current = current->next;
		if (current == NULL)
			add_env(env_list, new_str);
	}
}

// /*
//  * Permet de norme change_env_exp
// */
// static int	help_cee(char **current_name, t_main **current, char **result)
// {
// 	*current_name = ft_strdupto_n((*current)->str, '=');
// 	if (!*current_name)
// 	{
// 		free(*result);
// 		return (2);
// 	}
// 	return (0);
// }

// /*
//  * Permet de norme change_env_exp
// */
// static int	help_cee2(char **current_name, t_main **current, char **result,
// 		char **name_env)
// {
// 	if (ft_strncmp(*current_name, *name_env, ft_strlen(*current_name)) == 0
// 		&& ft_strlen(*current_name) == ft_strlen(*name_env))
// 	{
// 		if ((*current)->str)
// 				free((*current)->str);
// 		(*current)->str = ft_strdup(*result);
// 		free(*current_name);
// 		free(*result);
// 		return (0);
// 	}
// 	*current = (*current)->next;
// 	free(*current_name);
// 	return (1);
// }

// /*
//  * Permet de norme change_env_exp
// */
// static int	help_cee3(char **result)
// {
// 	free(*result);
// 	return (1);
// }

/* 
 * Modif de env pour export
 * Recherche de name_env dans env et modifs.
 * Boucle jusqu'a trouver name_env dans l'env.
 * Puis, modifie sa valeur avec value.
*/
int	change_env_exp(t_lexer **env_list, char *name_env, char *value)
{
	char	*result;
	char	*tmp;
	char	*current_name;
	t_lexer	*current;

	tmp = ft_strjoin(name_env, "=");
	if (! tmp)
		return (2);
	if (ft_strcmp(name_env, "SHLVL") == 0 && ft_strlen((const char *)name_env) \
		== 5 && ft_atoi(value) < 0)
		result = ft_strjoin(tmp, "0");
	else
		result = ft_strjoin(tmp, value);
	free(tmp);
	if (!result)
		return (2);
	current = *env_list;
	while (current)
	{
		current_name = ft_strdupto_n(current->str, '=');
		if (!current_name)
		{
			free(result);
			return (2);
		}
		if (ft_strncmp(current_name, name_env, ft_strlen(current_name)) == 0
			&& ft_strlen(current_name) == ft_strlen(name_env))
		{
			if (current->str)
				free(current->str);
			current->str = ft_strdup(result);
			free(current_name);
			free(result);
			return (0);
		}
		current = current->next;
		free(current_name);
	}
	free(result);
	return (1);
}
	// {
	// 	if (help_cee(&current_name, &current, &result) == 2)
	// 		return (2);
	// 	if (help_cee2(&current_name, &current, &result, &name_env) == 0)
	// 		return (0);
	// }
	// return (help_cee3(&result));
// }


// /*
//  * Permet de norme searchin_env
// */
// static int	help_s_e(t_main **temp, t_main **current, char **name_env)
// {
// 	*temp = (*current)->next->next;
// 	free((*current)->next);
// 	(*current)->next = *temp;
// 	free(*name_env);
// 	return (0);
// }

/* 
 * Boucle principale d'unset.
 * Cherche une VE et la supprime s'il la trouve.
*/
int	searchin_env(t_lexer **env_list, char *str)
{
	t_lexer	*current;
	t_lexer	*temp;
	char	*name_env;
	size_t	len;

	current = *env_list;
	len = ft_strlen(str);
	while (current && current->next)
	{
		name_env = ft_strdupto_n(current->next->str, '=');
		if (!name_env)
			return (1);
		if (ft_strncmp(str, name_env, len) == 0 && \
		len == ft_strlen(name_env))
			// return (help_s_e(&temp, &current, &name_env));
		{
			temp = current->next->next;
			free(current->next);
			current->next = temp;
			free(name_env);
			return (0);
		}
		free(name_env);
		current = current->next;
	}
	return (1);
}

/* 
 * Fonction a l'image de 'env'
 * Affiche l'environnement du shell en entier
 * (Attention : env -i ./minishell doit afficher PWD, SHLVL et _)
*/
int	ft_env(t_main *mini, t_parsing *parse, t_lexer **env_list)
{
	t_lexer	*current;

	parse->incr = 0;
	update_last_ve(parse, env_list);
	current = *env_list;
	if (parse->cmd_tab[parse->incr] == NULL)
		return (1);
	while (current)
	{
		// if (ft_strncmp(current->str, "?=", 2) == 0)
			// current = current->next;
		// else
		// {
			printf("%s\n", current->str);
			current = current->next;
		// }
	}
	mini->shell.error = handle_error_bis(0);
	return (0);
}

/*
 * Permet de norme set_env
*/
static int	help_set_env(t_lexer **env_list, char **env, int *i,
		char **identifier)
{
	add_env(env_list, env[*i]);
	*identifier = ft_strdupto_n(env[*i], '=');
	if (!*identifier)
		return (-1);
	return (0);
}

/*
 * Permet de norme set_env
*/
static int	help_set_env2(t_lexer **env_list, t_shell *shell, char **identifier,
		int *i)
{
	if (ft_strcmp(*identifier, "SHLVL") == 0
		&& ft_strlen(*identifier) == 5)
	{
		if (ft_plus_shell(shell, env_list) == 1)
			return (-1);
	}
	free(*identifier);
	(*i)++;
	return (0);
}

/* 
 * Initialise liste d'env 
*/
int	set_env(t_main *mini, char **env)
{
	int		i;
	char	*identifier;

	if (handle_env(mini) == -1)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		if (help_set_env(&mini->env_list, env, &i, &identifier) == -1)
			return (-1);
		if (help_set_env2(&mini->env_list, &mini->shell, &identifier, &i) == -1)
			return (-1);
		i ++;
	}
	add_env(&mini->env_list, "?=0");
	return (0);
}

/* 
 * Change env pour $?.
 * Mets a jour les cas d'erreurs de $?
*/
int	change_error(t_lexer **env_list, t_shell *shell, int value)
{
	t_lexer	*current;
	char	*current_name;
	char	*result;
	char 	*nb_char;

	nb_char = ft_itoa(value);
	if (!nb_char)
		return (2);
	result = ft_strjoin("?=", nb_char);
	if (!result)
	{
		free(nb_char);
		shell->error = value;
		return (2);
	}
	current = *env_list;
	while (current)
	{
		current_name = ft_strdupto_n(current->str, '=');
		if (!current_name)
		{
			free(nb_char);
			free(result);
			shell->error = value;
			return (2);
		}
		if (ft_strcmp(current_name, "?") == 0
			&& ft_strlen(current_name) == 1)
		{
			printf("change_error ???\n");
			if (current->str)
				free(current->str);
			current->str = ft_strdup(result);
			shell->error = value;
			free(current_name);
			free(nb_char);
			free(result);
			return (0);
		}
		free(current_name);
		current = current->next;
	}
	shell->error = value;
	free(nb_char);
	free(result);
	return (1);
}
