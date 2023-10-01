/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:03:10 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/01 22:29:22 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../../include/minishell.h"

int	expander_doll(t_main *mini, t_parsing *node, int i, int j)
{
	int env_index;
	int	ok;
	char *str_new;

	env_index = check_env_var(mini, node->cmd_tab[i], j);
	if (node->cmd_tab[i][j] == '$')
	{
		str_new = keep_good_str(mini->env, env_index);
		copy_past(node, i, j, str_new);
		ok = ft_strlen(str_new);
		free(str_new);
		return (ok);
	}
	return (1);
}

int get_rv(t_main *mini, t_parsing *node, int i, int j)
{
	char *str_new;

	(void)j;
	if (ft_strlen(node->cmd_tab[i]) == 2)
		str_new = ft_itoa(mini->return_value);
	else
		str_new = go_itoa_replace(mini, node->cmd_tab[i]);
	free(node->cmd_tab[i]);
	node->cmd_tab[i] = ft_strdup(str_new);
	free(str_new);
	return (2);
}

int    expanding_bis(t_main *mini, t_parsing *node, int i, int j)
{
    int    nb_env;

    nb_env = check_env_var(mini, node->cmd_tab[i], j);
    if (nb_env >= 0)
    {
        if (nb_env == 999)
            return (expand_dol_qt(mini, node, i, j));
        else
            return (expand_dollard(mini, node, i, j));
    }
    else if (nb_env == -1)
        return (rm_dollard(mini, node, i, j));
    else if (nb_env == -2)
        return (1);
    else if (nb_env == -3)
        return (return_value(mini, node, i, j));
    return (0);
}

int    second_expand(t_main *mini, t_parsing *node, int i, int j)
{
    if ((j < (int)ft_strlen(node->cmd_tab[i])) && node->cmd_tab[i][j])
    {
        while (node->cmd_tab[i][j])
        {
            if (node->cmd_tab[i][j] == '$')
            {
                while (node->cmd_tab[i][j] == '$')
                    j++;
                if (!node->cmd_tab[i][j])
                    break ;
                expanding(mini, node, i, j - 1);
            }
            j++;
            if ((int)ft_strlen(node->cmd_tab[i]) < j)
                return (0);
        }
    }
    if (j > (int)ft_strlen(node->cmd_tab[i]))
        return (0);
    if (!node->cmd_tab[i][j])
        return (0);
    return (1);
}

void    expanding(t_main *mini, t_parsing *node, int i, int j)
{
    int            dol;

    while ((j < (int)ft_strlen(node->cmd_tab[i])) && node->cmd_tab[i][j])
    {
        if (node->cmd_tab[i][j] == '$')
        {
            if (!node->cmd_tab[i][j + 1])
                return ;
            dol = j;
            j = while_dol(mini, node, i, dol);
            if (!j)
                return ;
            if (!second_expand(mini, node, i, j))
                return ;
        }
        j++;
    }
} */