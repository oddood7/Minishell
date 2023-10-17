/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:53:23 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 17:04:36 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Prompt: $USER:$PWD>
char	*prompt_cmd(t_shell *shell, char *user)
{
	char	*prompt;
	char	*username;
	char	*pwd;

	prompt = NULL;
	username = NULL;
	pwd = NULL;
	if (user != NULL)
		username = ft_strjoin(user, ":");
	if (shell->is_pwd != NULL)
		pwd = ft_strjoin(username, shell->is_pwd);
	prompt = ft_strjoin(pwd, ">");
	return (prompt);
}
