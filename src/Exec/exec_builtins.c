/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:54:28 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 18:54:28 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_3(t_main *mini, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "unset", len) && len == 5)
	{
		ft_unset(mini, mini->cmd_parse, &mini->env_list);
		free_garbage();
		exit(mini->shell.error);
	}
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
	{
		ft_echo(mini, mini->cmd_parse);
		free_garbage();
		exit(mini->shell.error);
	}
}

void	find_2(t_main *mini, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "exit", len) && len == 4)
	{
		ft_exit(mini, mini->cmd_parse);
	}
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
	{
		ft_export(mini, mini->cmd_parse);
		free_garbage();
		exit(mini->shell.error);
	}
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
	{
		ft_pwd(mini);
		free_garbage();
		exit(mini->shell.error);
	}
	else
		find_3(mini, cmd, len);
}

void	find(t_main *mini, t_parsing *node)
{
	char	*cmd;
	int		len;

	if (node->cmd_tab[0] == NULL)
		return ;
	mini->cmd_parse->incr = 0;
	cmd = node->cmd_tab[0];
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", len) && len == 2)
	{
		ft_cd(mini, mini->cmd_parse);
		free_garbage();
		exit(mini->shell.error);
	}
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
	{
		ft_env(mini, mini->cmd_parse, &mini->env_list);
		free_garbage();
		exit(mini->shell.error);
	}
	else
		find_2(mini, cmd, len);
}

int	first_builtins2(t_main *mini, t_parsing *node, int len)
{
	if (!ft_strncmp(node->cmd_tab[0], "unset", len) && node->next == NULL
		&& len == 5)
	{
		ft_unset(mini, node, &mini->env_list);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "export", len) && node->next == NULL
		&& len == 6)
	{
		ft_export(mini, node);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "cd", len) && node->next == NULL
		&& len == 2)
	{
		if (mini->pipe_count)
			return (0);
		ft_cd(mini, node);
		return (1);
	}
	return (0);
}

int	first_builtins(t_main *mini, t_parsing *node)
{
	int	len;

	node->incr = 0;
	if (node->cmd_tab[0])
		len = ft_strlen(node->cmd_tab[0]);
	if (node->cmd_tab[0] == NULL)
		return (0);
	if (first_builtins2(mini, node, len))
		return (1);
	if (!ft_strncmp(node->cmd_tab[0], "exit", len) && len == 4)
	{
		if (mini->pipe_count)
			return (0);
		ft_exit(mini, node);
		return (1);
	}
	return (0);
}
