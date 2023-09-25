/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:23:02 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/23 18:48:07 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_main	*init_env(char **envp)
{
	t_main *env;
	
}
int init_minishell(t_main *mini, char *str)
{
	mini->input_line = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!mini->input_line)
		return (0);
	do_lexer(mini);
	if (!do_lexer(mini))
		printf("failed to lex");
	return (0);
}

void main_loop(t_main *minishell)
{
	char *buff;

	while (1)
	{
		buff = readline("minishell$> ");
		if (buff)
			add_history(buff);
		init_minishell(minishell, buff);
		free (buff);
	}
	clear_history();
}

int main(int ac, char **av)
{
	t_main minishell;
	(void)av;
	if (ac != 1)
		return (printf("more than one argument"));
	main_loop(&minishell);
	return (0);
}