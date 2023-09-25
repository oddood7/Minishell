/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:37:01 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/25 19:06:04 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_env(t_main *mini, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(char *) * i + 1);
	if (!mini->env)
		return (erreur_mall(mini));
	i = 0;
	while (env[i])
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = 0;
}