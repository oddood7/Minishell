/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:03:17 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 14:53:09 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	shell_change_path(t_shell *shell, char *value)
{
	int		i;

	i = 0;
	shell->path = ft_strdup(value);
	if (!shell->path)
		return (1);
	if (shell->path != NULL && ft_strlen(shell->path) >= 5)
	{
		shell->cmd_paths = ft_split(shell->path + 5, ':');
		if (! shell->cmd_paths)
			return (-1);
	}
	return (0);
}

/* 
 * Changement des valeurs de la structure t_shell.
 * S'effectue apres unset (et export aussi !!)
*/
void	shell_change(t_shell *shell, char *str, char *value)
{
	int		len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "HOME", len) == 0)
		shell->home = ft_strdup(value);
	else if (ft_strncmp(str, "OLDPWD", len) == 0)
		shell->oldpwd = ft_strdup(value);
	else if (ft_strncmp(str, "PWD", len) == 0)
		shell->pwd = ft_strdup(value);
	else if (ft_strncmp(str, "PATH", len) == 0)
		shell_change_path(shell, value);
	else if (ft_strncmp(str, "SHLVL", len) == 0)
		shell->shlvl = ft_strdup(value);
}
