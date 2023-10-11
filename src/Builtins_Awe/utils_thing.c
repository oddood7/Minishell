/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:49:57 by asalic            #+#    #+#             */
/*   Updated: 2023/10/11 15:53:23 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Check si getenv est NULL
 * Si oui, renvoit une chaine vide
 * Renvoit un char * de la valeur de la ve enregistree
*/
char *get_env_var(const char *name)
{
	char	*env_var;

	env_var = getenv(name);
	if (! env_var)
		env_var = "";
	return (ft_strdup(env_var));
}

/* 
 * Creer les maillons shell->str en fonction de getenv
 * Check cas d'erreurs
*/
int	handle_env(t_main *mini)
{
	mini->shell.home = get_env_var("HOME");
	mini->shell.user = get_env_var("USER");
	mini->shell.pwd = get_env_var("PWD");
	mini->shell.is_pwd = get_env_var("PWD");
	mini->shell.is_oldpwd = get_env_var("OLDPWD");
	mini->shell.oldpwd = get_env_var("OLDPWD");
	mini->shell.path = get_env_var("PATH");
	mini->shell.shlvl = get_env_var("SHLVL");
	mini->shell.error = 0;
	if (mini->shell.path != NULL && mini->shell.path[0] != '\0')
	{
		mini->shell.cmd_paths = ft_split(mini->shell.path + 5, ':');
		if (! mini->shell.cmd_paths)
			return (-1);
	}
	return (0);
}

int	handle_error_bis(int code_err)
{
	int	final_error;

	final_error = 0;
	printf("\e[32mMON CODE ERREUR \e[m: %d\n", code_err);
	if (code_err == 13 || code_err == 12)
		final_error = 126;
	else if (code_err == 11)
		final_error = 127;
	else if (code_err == 0 && g_error != 0)
		final_error = g_error;
	else
		final_error = code_err;
	return (final_error);
}

/*
 * Compare 2 string
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*
 * Fonction utilitaire, libere chaque maillon de la chaine d'arguments
 * conserve *liste et le reset a NULL
*/
void	clear_args_list(t_lexer **list)
{
	t_lexer	*current;
	t_lexer	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
	}
	*list = NULL;
}
