/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:34:51 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 17:04:01 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Change de repertoire en fonction du buf envoye.
 * Agit reellement comme la commande cd.
*/
int	cd_real_version(char *buf, t_main *mini, t_parsing *parse)
{
	if (chdir(buf) == -1)
	{
		ft_printf("%s: %s: %s\n", parse->cmd_tab[parse->incr], buf, strerror(errno));
		// mini->shell.error = handle_error_bis(errno -1);
		return (errno);
	}
	else
	{
		if (!cd_move_and_change(mini->env_list, &mini->shell))
			return (1);
	}
	return (0);
}

/*
 * Code erreur cd :fichier introuvable et return.
*/
static char *help_itp1(t_main *mini, DIR **dir,
		char **temp)
{
	ft_printf("cd : No such file of directory\n");
	mini->shell.error = handle_error_bis(0);
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
static char	*is_two_points(t_main *mini, t_parsing *parse)
{
	DIR		*dir;
	char	*temp;
	char	*buf;

	if (ft_strcmp(mini->shell.is_pwd, getenv("PWD")))
	{
		free(mini->shell.is_pwd);
		mini->shell.is_pwd = get_env_var("PWD");
	}
	temp = from_end_to_char(mini->shell.is_pwd, '/');
	if (!temp)
		return (NULL);
	dir = opendir(temp);
	ft_printf("temp = %s\n", temp);
	if (dir == NULL)
		return (help_itp1(mini, &dir, &temp));
	buf = ft_strdup(parse->cmd_tab[parse->incr +1]);
	if (! buf)
		help_itp2(&dir, &temp);
	if (mini->shell.pwd == NULL)
	{
		if (!cd_move_and_change(mini->env_list, &mini->shell))
			return(help_itp2(&dir, &temp));
	}
	help_itp2(&dir, &temp);
	return (buf);
}

/* 
 * Check les arguments de cd
 * Gere cas d'erreurs premiers
*/
static int	check_cd(t_parsing *parse, t_main *mini)
{
	if (parse->cmd_tab[parse->incr +1] && parse->cmd_tab[parse->incr +1][0] == '\0')
		return (1);
	if (parse->cmd_tab[parse->incr +1] == NULL || ft_strncmp(parse->cmd_tab[parse->incr +1], "~",
			ft_strlen(parse->cmd_tab[parse->incr +1])) == 0)
	{
		if (mini->shell.home == NULL)
		{
			ft_printf("%s: 'HOME' not set\n", parse->cmd_tab[parse->incr]);
			mini->shell.error = handle_error_bis(1);
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
	cod = check_cd(parse, mini);
	if (cod == 1)
		return (1);
	if (cod == 2)
		buf = ft_strdup(mini->shell.home);
	else if (ft_strncmp(parse->cmd_tab[parse->incr +1], "..", ft_strlen(parse->cmd_tab[parse->incr +1])) == 0)
		buf = is_two_points(mini, parse);
	else
		buf = ft_strdup(parse->cmd_tab[parse->incr +1]);
	if (!buf)
		return (1);
	err = cd_real_version(buf, mini, parse);
	free(buf);
	parse->incr = 0;
	mini->shell.error = handle_error_bis(err);
	return (0);
}
