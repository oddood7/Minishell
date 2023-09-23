/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:23:02 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/22 21:23:25 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exit_code = 0;

t_main *init_minishell(char **envp)
{
	t_main *mini;

	mini = ft_calloc(1, sizeof(t_main));
	if (mini != NULL && envp != NULL && *envp != NULL)
	{
		mini->env = ft_strdup_tab(envp);
		mini->tmp = NULL;
		return (mini);
	}
	return (NULL);
}

void free_minishell(t_main *minishell)
{
	if (minishell->env)
		ft_free_tab(minishell->env);
	if (minishell->tmp)
		ft_free_tab(minishell->tmp);
	free(minishell);
}

void main_loop(t_main *minishell)
{
	char *buff;
	(void)minishell;
	while (1)
	{
		buff = readline("minishell$> ");
		if (buff && ft_strlen(buff) > 0)
			add_history(buff);
	}
}

int main(int ac, char **av, char **envp)
{
	t_main *minishell;
	
	if (ac >= 1 && av[0] != NULL && envp != NULL && envp[0] != NULL)
	{
		minishell = init_minishell(envp);
		if (minishell != NULL)
		{
			create_env(minishell);
			//do_builtins(minishell, exec);
			main_loop(minishell);
			free_minishell(minishell);
		}
	}
	return (exit_code);
}