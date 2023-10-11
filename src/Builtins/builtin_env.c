/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:14:51 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 13:21:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	built_env(t_main *mini, t_parsing *node)
{
	(void)node;
	int i;

	i = 0;
	while (mini->env[i++])
		ft_putendl_fd(mini->env[i], 1);
	mini->shell.error = 0;
	return (0);
}

int		built_pwd(t_main *mini, t_parsing *parse)
{
	char *cwd;

	(void)mini;
	(void)parse;
	cwd = malloc(2048);
	if (!cwd)
		return (0);
	if (getcwd(cwd, 2048) == NULL)
		ft_putendl_fd("cwd problem", 1);
	else
		ft_putendl_fd(cwd, 1);
	free(cwd);
	mini->shell.error = 0;
	return (0);
}