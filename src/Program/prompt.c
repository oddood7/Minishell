/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:53:23 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 19:27:13 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    bf_prd(char *str, int d, char *color)
{
    char    *str_cara;
    char    *color_strdup;
    int        idx_str;
    int        idx;

    color_strdup = ft_strdup(color);
    idx_str = 0;
    write(1, color_strdup, ft_strlen(color));
    free(color_strdup);
    while (str[idx_str])
    {
        idx = 0;
        while (idx < d)
            idx++ ;
        str_cara = (char*)malloc(2 * sizeof(char));
        str_cara[0] = str[idx_str];
        str_cara[1] = '\0';
        write(1, str_cara, 1);
        free(str_cara);
        idx_str++ ;
    }
    color_strdup = ft_strdup("\033[0m");
    write(1, color_strdup, ft_strlen(color_strdup));
    free(color_strdup);
}

static char	*ft_join_strdup_right(char *s1, char *s2)
{
	char	*s2_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s2_strdup = ft_strdup(s2);
	var_join_strdup = ft_strjoin(s1, s2_strdup);
	return (var_join_strdup);
}

char	*ft_join_strdup_left(char *s1, char *s2)
{
	char	*s1_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_strdup = ft_strdup(s1);
	var_join_strdup = ft_strjoin(s1_strdup, s2);
	return (var_join_strdup);
}

char	*ft_join_strdup(char *s1, char *s2)
{
	char	*s1_strdup;
	char	*s2_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_strdup = ft_strdup(s1);
	s2_strdup = ft_strdup(s2);
	var_join_strdup = ft_strjoin(s1_strdup, s2_strdup);
	return (var_join_strdup);
}

char	*build_color(char *c1, char *str, int dup_str)
{
	char	*color_builded;

	if (dup_str == 0)
		color_builded = ft_join_strdup(c1, str);
	if (dup_str == 1)
		color_builded = ft_join_strdup_left(c1, str);
	color_builded = ft_join_strdup_right(color_builded, "\001\e[0m\002");
	if (!color_builded)
		return (NULL);
	return (color_builded);
}

/* Prompt: $USER:$PWD>
 * Je pourrais mettre des couleurs si tu veux que ca ressorte mieux
 * A voir si je laisse les couleurs ou pas en fonction des free a faire
*/
char	*prompt_cmd(t_shell *shell, char *user)
{
	char	*prompt;
	char	*common;
	char	*username;
	char	*pwd;

	prompt = NULL;
	username = NULL;
	pwd = NULL;
	common = NULL;
	if (user != NULL)
		username = build_color("\033[1;34m", ft_strjoin(user, ":"), 0);
	if (shell->is_pwd != NULL)
		pwd = build_color("\033[1;32m", shell->is_pwd, 0);
	// pwd = ft_strjoin(username, shell->is_pwd);
	common = ft_strjoin(username, pwd);
	prompt = ft_strjoin(common, ">");
	free(username);
	free(pwd);
	return (prompt);
}
