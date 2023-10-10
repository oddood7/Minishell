/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:34:51 by asalic            #+#    #+#             */
/*   Updated: 2023/10/10 15:16:51 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Change de repertoire en fonction du buf envoye.
 * Agit reellement comme la commande cd.
*/
int	cd_real_version(char *buf, t_shell *shell, t_lexer *env_list, t_parsing *parse)
{
	if (chdir(buf) == -1)
	{
		printf("%s: %s: %s\n", parse->cmd_tab[parse->incr], buf, strerror(errno));
		change_error(&env_list, shell, handle_error_bis(errno -1));
		return (1);
	}
	else
	{
		if (!cd_move_and_change(env_list, shell))
			return (1);
	}
	return (0);
}

/*
 * Code erreur cd :fichier introuvable et return.
*/
static char *help_itp1(t_lexer *env_list, t_shell **shell, DIR **dir,
		char **temp)
{
	printf("cd : No such file of directory\n");
	change_error(&env_list, *shell, 0);
	closedir(*dir);
	free(*temp);
	return (NULL);
}

/*
 * Free and close in cd
*/
static char	*help_itp2(DIR **dir, char **temp)
{
	free(*temp);
	closedir(*dir);
	return (NULL);
}

/*
 * Cas ou cd.., suite de la commande cd principale
*/
static char	*is_two_points(t_shell *shell, t_parsing *parse, t_lexer *env_list)
{
	DIR		*dir;
	char	*temp;
	char	*buf;

	temp = from_end_to_char(shell->is_pwd, '/');
	if (!temp)
		return (NULL);
	dir = opendir(temp);
	if (dir == NULL)
		return (help_itp1(env_list, &shell, &dir, &temp));
	buf = ft_strdup(parse->cmd_tab[parse->incr +1]);
	if (! buf)
		help_itp2(&dir, &temp);
	if (shell->pwd == NULL)
	{
		if (!cd_move_and_change(env_list, shell))
			return(help_itp2(&dir, &temp));
	}
	help_itp2(&dir, &temp);
	return (buf);
}

/* 
 * Check les arguments de cd
 * Gere cas d'erreurs premiers
*/
int	check_cd(t_parsing *parse, t_shell *shell, t_lexer *env_list)
{
	if (parse->cmd_tab[parse->incr +1] && parse->cmd_tab[parse->incr +1][0] == '\0')
		return (1);
	if (parse->cmd_tab[parse->incr +1] == NULL || ft_strncmp(parse->cmd_tab[parse->incr +1], "~",
			ft_strlen(parse->cmd_tab[parse->incr +1])) == 0)
	{
		if (shell->home == NULL)
		{
			printf("%s: 'HOME' not set\n", parse->cmd_tab[parse->incr]);
			change_error(&env_list, shell, 1);
			return (1);
		}
		return (2);
	}
	return (0);
}

/* 
 * Check si cd .. || cd ~ || autre cd
 * Agit en fonction des cas speciaux, un peu comme une gestionnaire
 * d'arguments pour cd specifiquement.
*/
int	ft_cd(t_main *mini, t_parsing *parse)
{
	char	*buf;
	int		cod;
	int		err;

	parse->incr = 0;
	printf("str : %s\n", parse->cmd_tab[0]);
	cod = check_cd(parse, &mini->shell, mini->env_list);
	if (cod == 1)
		return (1);
	if (cod == 2)
		buf = ft_strdup(mini->shell.home);
	else if (ft_strncmp(parse->cmd_tab[parse->incr +1], "..", ft_strlen(parse->cmd_tab[parse->incr +1])) == 0)
		buf = is_two_points(&mini->shell, parse, mini->env_list);
	else
		buf = ft_strdup(parse->cmd_tab[parse->incr +1]);
	if (!buf)
		return (1);
	err = cd_real_version(buf, &mini->shell, mini->env_list, parse);
	free(buf);
	parse->incr = 0;
	return (err || change_error(&mini->env_list, &mini->shell, 0) == 1);
}
