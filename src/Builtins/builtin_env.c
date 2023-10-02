/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:14:51 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/02 19:07:15 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	built_env(t_main *mini)
{
	int i;

	i = 0;
	while (mini->env[i++])
		ft_putendl_fd(mini->env[i], 1);
	mini->return_value = 0;
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
	mini->return_value = 0;
	return (0);
}