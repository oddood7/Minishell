/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:54:56 by asalic            #+#    #+#             */
/*   Updated: 2023/10/13 16:31:42 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Check les erreurs de export
 * check si l'argument est NULL ou s'il existe mais qu'il est vide
 * ATTENTION: voir cas speciaux et faire mini parsing des args avant d'export.
*/
static int	export_errors(t_parsing *parse, t_main *mini)
{
	if (ft_strlen(parse->cmd_tab[parse->incr]) == 6 && ft_strcmp(parse->cmd_tab[parse->incr], "export") == 0
		&& !parse->cmd_tab[parse->incr +1])
	{
		export_out_main(mini);
		return (1);
	}
	else if (ft_strlen(parse->cmd_tab[parse->incr]) == 6 && ft_strcmp(parse->cmd_tab[parse->incr], "export") == 0)
		parse->incr ++;
	if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr][0] == '\0')
	{
		ft_printf("export : \"\": invalid identifier\n");
		mini->shell.error = handle_error_bis(1);
		return (1);
	}
	if (parse->cmd_tab[parse->incr] && parse_export(parse->cmd_tab[parse->incr]) == 2)
		return (0);
	else if (parse->cmd_tab[parse->incr] && parse_export(parse->cmd_tab[parse->incr]) == 1)
	{
		ft_printf("export : \"%s\" : invalid identifier\n", parse->cmd_tab[parse->incr]);
		mini->shell.error = handle_error_bis(1);
		return (1);
	}
	return (0);
}

/* 
 * Gere les boucles de export pour changer les VE et sinon les creer
*/
static void	ft_more_export(t_shell *shell, char *v_env, char *value)
{
	if (ft_strcmp(v_env, "SHLVL") == 0 && ft_strlen(v_env) == 5
		&& ft_atoi(value) < 0)
		value = "0";
	shell_change(shell, v_env, value);
	if (ft_strncmp(v_env, "PWD", ft_strlen(v_env)) == 0)
	{
		free(shell->is_pwd);
		shell->is_pwd = ft_strdup(value);
	}
	else if (ft_strncmp(v_env, "OLDPWD", ft_strlen(v_env)) == 0)
	{
		free(shell->is_oldpwd);
		shell->is_oldpwd = ft_strdup(value);
	}
}

/* Fonction export.
 * Cherche d'abord si la VE existe deja.
 * Si oui, la modifie, dans env_list et dans shell.
 * Si non, la creee dans env_list seulement.
 * Gere le cas ou il y a plusieurs creation/remplacement de VE

*/
int	ft_export(t_main *mini, t_parsing *parse)
{
	char	*value;
	char	*v_env;
	int		result_change_env;

	ft_printf("arg 1 : %s\n", parse->cmd_tab[0]);
	ft_printf("arg 2 : %s\n", parse->cmd_tab[1]);
	ft_printf("arg 3 : %s\n", parse->cmd_tab[2]);
	if (export_errors(parse, mini) == 1)
	{
		if (parse->cmd_tab[parse->incr +1] != NULL)
		{
			parse->incr ++;
			ft_export(mini, parse);
		}
		return (1);
	}
	if (ft_strchr(parse->cmd_tab[parse->incr], '='))
	{
		v_env = ft_strdupto_n(parse->cmd_tab[parse->incr], '=');
		if (! v_env)
			return (1);
		value = ft_strdup_from(parse->cmd_tab[parse->incr], '=');
		if (! value)
		{
			free(v_env);
			return (1);
		}
		result_change_env = change_env_exp(&mini->env_list, v_env, value);
		if (result_change_env == 0)
			ft_more_export(&mini->shell, v_env, value);
		else if (result_change_env == 1)
		{
			add_env(&mini->env_list, parse->cmd_tab[parse->incr]);
			ft_more_export(&mini->shell, v_env, value);
		}
		else
		{
			free(v_env);
			free(value);
			return (1);
		}
		free(v_env);
		free(value);
	}
	if (parse->cmd_tab[parse->incr +1] != NULL)
	{
		parse->incr ++;
		ft_export(mini, parse);
	}
	mini->env = env_to_char(&mini->env_list);
	mini->shell.error = handle_error_bis(0);
	return (0);
}

/*
 * Gere export sans args
 * Affiche: declare -x VE env
*/
int	export_out_main(t_main *mini)
{
	char	*bfore;
	char	*after;
	char	**env_sort;
	int		i;

	bfore = NULL;
	after = NULL;
	env_sort = ft_sort(&mini->env_list);
	i = 0;
	while (env_sort[i])
	{
		bfore = ft_strdupto_n(env_sort[i], '=');
		after = ft_strdup_from(env_sort[i], '=');
		if (ft_strncmp(bfore, "?=", 2) == 0)
			i ++;
		else
			ft_printf("declare -x %s=\"%s\"\n", bfore, after);
		i ++;
		free(bfore);
		free(after);
	}
	i = 0;
	while (env_sort[i])
		free(env_sort[i++]);
	free(env_sort);
	mini->shell.error = handle_error_bis(0);
	// update_last_ve(mini->cmd_parse, &mini->env_list);
	return (0);
}

/* 
 * Mini parsing des args d'export
 * Check si le nom est conforme, juste des chiffres, des lettres et des
 * underscores
*/
int	parse_export(char *str)
{
	int	i;

	i = 0;
	if (!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a'
			&& str[0] <= 'z'))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] \
			>= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' \
			&& str[i] <= 'z') && str[i] != '_')
			return (1);
		i ++;
	}
	if (str[i] == '=')
		return (0);
	return (2);
}
