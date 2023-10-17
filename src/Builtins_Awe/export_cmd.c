/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:54:56 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 16:26:22 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Suite de export_errors */
static int	exp_err_parse(t_parsing *parse, t_main *mini)
{
	if (parse->cmd_tab[parse->incr] && \
		parse_export(parse->cmd_tab[parse->incr]) == 2)
		return (0);
	else if (parse->cmd_tab[parse->incr] && \
		parse_export(parse->cmd_tab[parse->incr]) == 1)
	{
		ft_printf("export : \"%s\" : invalid identifier\n", \
			parse->cmd_tab[parse->incr]);
		mini->shell.error = handle_error_bis(1);
		return (1);
	}
	return (0);
}

/* 
 * Check les erreurs de export
 * check si l'argument est NULL ou s'il existe mais qu'il est vide
 * ATTENTION: voir cas speciaux et faire mini parsing des args avant d'export.
*/
static int	export_errors(t_parsing *parse, t_main *mini)
{
	if (ft_strlen(parse->cmd_tab[parse->incr]) == 6 && \
		ft_strcmp(parse->cmd_tab[parse->incr], "export") == 0
		&& !parse->cmd_tab[parse->incr +1])
	{
		export_out_main(mini);
		return (1);
	}
	else if (ft_strlen(parse->cmd_tab[parse->incr]) == 6 && \
		ft_strcmp(parse->cmd_tab[parse->incr], "export") == 0)
		parse->incr ++;
	if (parse->cmd_tab[parse->incr] && parse->cmd_tab[parse->incr][0] \
		== '\0')
	{
		ft_printf("export : \"\": invalid identifier\n");
		mini->shell.error = handle_error_bis(1);
		return (1);
	}
	if (exp_err_parse(parse, mini) == 1)
		return (1);
	return (0);
}

/* Gere les boucles de export pour changer les VE et sinon les creer */
static void	ft_more_export(t_shell *shell, char *v_env, char *value)
{
	if (ft_strcmp(v_env, "SHLVL") == 0 && ft_strlen(v_env) == 5
		&& ft_atoi(value) < 0)
		value = "0";
	shell_change(shell, v_env, value);
	if (ft_strncmp(v_env, "PWD", ft_strlen(v_env)) == 0)
		shell->is_pwd = ft_strdup(value);
	else if (ft_strncmp(v_env, "OLDPWD", ft_strlen(v_env)) == 0)
		shell->is_oldpwd = ft_strdup(value);
}

static int	exp_parse_ok(t_parsing *parse, t_main *mini)
{
	char	*value;
	char	*v_env;
	int		result_change_env;

	v_env = ft_strdupto_n(parse->cmd_tab[parse->incr], '=');
	value = ft_strdup_from(parse->cmd_tab[parse->incr], '=');
	result_change_env = change_env_exp(&mini->env_list, v_env, value);
	if (result_change_env == 0)
		ft_more_export(&mini->shell, v_env, value);
	else if (result_change_env == 1)
	{
		add_env(&mini->env_list, parse->cmd_tab[parse->incr]);
		ft_more_export(&mini->shell, v_env, value);
	}
	else
		return (1);
	return (0);
}

/* 
 * Fonction export.
 * Cherche d'abord si la VE existe deja.
 * Si oui, la modifie, dans env_list et dans shell.
 * Si non, la creee dans env_list seulement.
 * Gere le cas ou il y a plusieurs creation/remplacement de VE
*/
int	ft_export(t_main *mini, t_parsing *parse)
{
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
		if (exp_parse_ok(parse, mini) == 1)
			return (1);
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
