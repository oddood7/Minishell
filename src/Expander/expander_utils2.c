/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:18:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:39:46 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_char_after(t_parsing *node, int i, int j_dol)
{
	int		start;
	char	*tmp_str;

	while (node->cmd_tab[i][j_dol] != ' ')
	{
		if (node->cmd_tab[i][j_dol + 1] == '\0')
			return (NULL);
		else if (node->cmd_tab[i][j_dol + 1] == '$' || \
		node->cmd_tab[i][j_dol + 1] == '-' || node->cmd_tab[i] \
		[j_dol + 1] == ':' || node->cmd_tab[i][j_dol + 1] == '.')
		{
			j_dol += 1;
			break ;
		}
		j_dol++;
	}
	start = j_dol;
	while (node->cmd_tab[i][j_dol])
		j_dol++;
	tmp_str = ft_substr(node->cmd_tab[i], start, (j_dol - start));
	return (tmp_str);
}

int	copy_bis(char *s1, char *s2, int i, int ok)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	if (ok)
		s1[i] = '\0';
	return (i);
}

int	copy_past(t_parsing *cmd_node, int i, int j_dol, char *str_replace)
{
	int		k;
	int		len;
	char	*tmp_str;
	char	*s_after;

	k = 0;
	s_after = check_char_after(cmd_node, i, j_dol);
	len = ft_strlen(str_replace);
	tmp_str = just_alloc(len, j_dol, s_after);
	if (tmp_str == NULL)
		return (-123);
	while (k < j_dol)
	{
		tmp_str[k] = cmd_node->cmd_tab[i][k];
		k++;
	}
	if (s_after)
		k = copy_bis(tmp_str, str_replace, k, 0);
	else
		k = copy_bis(tmp_str, str_replace, k, 1);
	if (s_after)
		copy_bis(tmp_str, s_after, k, 1);
	cmd_node->cmd_tab[i] = ft_strdup(tmp_str);
	return (0);
}

char	*keep_good_str(char **env, int nb_env)
{
	int		i;
	int		start;
	int		size;
	char	*str_dol;

	i = 0;
	while (env[nb_env][i] && env[nb_env][i] != '=')
		i++;
	i += 1;
	start = i;
	size = i;
	while (env[nb_env][i])
	{
		size++;
		i++;
	}
	str_dol = ft_substr(env[nb_env], start, size);
	if (!str_dol)
	{
		free_garbage();
		exit(1);
	}
	return (str_dol);
}

char	*go_itoa_replace(t_main *data, char *s)
{
	char	*ok;
	char	*tmp_rv;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	tmp_rv = ft_itoa(data->return_value);
	ok = ft_malloc(sizeof(char) * ft_strlen(s) + 2);
	while (s[i] != '$')
	{
		ok[i] = s[i];
		i++;
	}
	k = i + 2;
	while (tmp_rv[j])
		ok[i++] = tmp_rv[j++];
	while (s[k])
		ok[i++] = s[k++];
	ok[i] = '\0';
	return (ok);
}
