/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:21:19 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/25 19:47:42 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void env_pwd_exec(t_main *mini, t_parsing *parse)
{
	int len;
	char *cmd;

	cmd = parse->cmd_tab[0];
	len = ft_strlen(cmd);
	if (parse->cmd_tab[0] == NULL)
		return ;
	if (!ft_strncmp(cmd, "env", len))
	{
		env_builtin(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cmd, "pwd", len))
	{
		pwd_builtin(mini, parse);
		exit (mini->return_value);
	}
}