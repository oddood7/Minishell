/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:10:53 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 14:22:29 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* int	has_variable(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_varname_len(char *str)
{
	int	len;

	len = 1;
	while (str[len] > ' ' && str[len] < 127 && str[len] != '$')
		len++;
	return (len - 1);
}

char	*var_hd_name(t_main *mini, char *input)
{
	int		i;
	int		len;
	char	*name;

	(void)(mini);
	i = 1;
	len = ft_varname_len(input);
	name = ft_malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		printf("ERROR MALLOC : GET VAR NAME (here_doc manage)");
		free_garbage();
		exit (1);
	}
	len = 0;
	while (input[i] != '$' && input[i] > ' ' && input[i] < 127)
	{
		name[len] = input[i];
		i++;
		len++;
	}
	name[len] = 0;
	return (name);
}

char	*get_var_content(t_main *mini, char *var_name)
{
	int		i;
	char	**envp;
	int		len;

	len = ft_strlen(var_name);
	i = 0;
	envp = mini->env;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], len))
			return (envp[i] + len + 1);
		i++;
	}
	i = 0;
	return (NULL);
}

int	here_doc_var(t_main *mini, char *input, int i, int fd[2])
{
	char	*var_name;
	char	*var_content;
	int		len;

	var_name = var_hd_name(mini, input + i);
	var_content = get_var_content(mini, var_name);
	if (var_content != NULL)
		write(fd[1], var_content, ft_strlen(var_content));
	len = ft_strlen(var_name) + 1;
	//free(var_name);
	return (len);
} */