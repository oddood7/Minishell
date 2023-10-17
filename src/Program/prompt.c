/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:53:23 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 15:39:52 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Prompt: $USER:$PWD>
 * Je pourrais mettre des couleurs si tu veux que ca ressorte mieux
 * A voir si je laisse les couleurs ou pas en fonction des free a faire
*/
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
