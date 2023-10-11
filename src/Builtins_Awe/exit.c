/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:09:25 by asalic            #+#    #+#             */
/*   Updated: 2023/10/11 11:36:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_shell_var(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->is_oldpwd)
		free(shell->is_oldpwd);
	if (shell->is_pwd)
		free(shell->is_pwd);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->home)
		free(shell->home);
	if (shell->path)
		free(shell->path);
	if (shell->input_bis)
		free(shell->input_bis);
	if (shell->shlvl)
		free(shell->shlvl);
	if (shell->cmd_paths)
	{
		while (shell->cmd_paths[i])
			free(shell->cmd_paths[i++]);
		free(shell->cmd_paths);
	}
	i = 0;
	if (shell->input)
	{
		while (shell->input[i])
			free(shell->input[i++]);
		free(shell->input);
	}
}

void	free_everything(t_shell *shell, t_lexer *list, t_lexer *env_list)
{
	free_shell_var(shell);
	if (env_list)
		clear_args_list(&env_list);
	rl_clear_history();
	clear_args_list(&list);
}

/*
 * Program stop.
 * Fonction a l'image de 'exit' 
 * Quitte le programme proprement avec free.
 * :warning:
 * wait(100) supprime de la premiere ligne pour la norme
*/
int	ft_exit(t_main *mini, t_parsing *parse)
{
	int	code_err;

	code_err = 0;
	printf("exit\n");
	if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1] \
		&& is_numeric(parse->cmd_tab[parse->incr +1]) == 1)
	{
		printf("%s: %s: numeric argument required\n", parse->cmd_tab[parse->incr],
			parse->cmd_tab[parse->incr +1]);
		code_err = 2;
	}
	else if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1] \
		&& parse->cmd_tab[parse->incr +2])
	{
		printf("%s: too many arguments\n", parse->cmd_tab[parse->incr]);
		change_error(&mini->env_list, &mini->shell, 1);
		return (1);
	}
	else if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr +1])
		code_err = ft_atoi(parse->cmd_tab[parse->incr +1]) % 256;
	else if (mini->shell.error == 0 && g_error != 0)
		code_err = g_error;
	else
		code_err = mini->shell.error;
	built_in_free(mini);
	exit(code_err);
}
