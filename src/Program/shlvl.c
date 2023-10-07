/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:35:03 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/07 21:53:57 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	shlvl_err(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	do_shlvl(t_main *mini, char **env)
{
	int shlvl;
	char *value;
	char *shell;
	char *new_shell;

	shell = find_var_env(env, "SHLVL");
	if (!shell)
		return ;
	value = value_env_var(mini, shell);
	if (!value || shlvl_err(value))
		return ;
	shlvl = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(shlvl);
	new_shell = ft_strjoin("SHLVL=", value);
	change_var_value(mini, new_shell, shell);
	free(value);
	free(new_shell);
}