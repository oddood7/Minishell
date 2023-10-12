/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:08:26 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/11 01:19:49 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_free_hd(t_main *mini, t_parsing *node, char *input, int check)
{
	int	i;

	i = 0;
	if (check != -42)
	{
		printf("\nbash: warning: here-document at line %d ", check);
		printf("deliminited by end-of-file");
		printf("(wanted `%s')\n", node->redirection->str);
	}
	free(input);
	while (i < mini->hd_count)
	{
		if (mini->here_doc[i].pos == 0)
			break ;
		close(mini->here_doc[i].fd[0]);
		close(mini->here_doc[i].fd[1]);
		i++;
	}
	free(mini->here_doc);
	ft_free_tab(mini->cmd_paths);
	ft_free_tab(mini->env);
	ft_free_tab(mini->env_exp);
	resets(mini);
	exit (1);
}

void	write_hd(t_main *mini, char *input, int fd[2])
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != ' ')
			i += here_doc_var(mini, input, i, fd);
		else
		{
			write(fd[1], &input[i], 1);
			i++;
		}
	}
	write(fd[1], "\n", 1);
	free(input);
}

char	*skip_tmpr(t_lexer *tmpr)
{
	char	*str;

	while (tmpr)
	{
		if (tmpr->operateur == LEFT_LEFT)
		{
			str = tmpr->str;
			return (str);
		}
		tmpr = tmpr->next;
	}
	return (NULL);
}

int	hdc_process(t_main *mini, t_parsing *node, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		here_doc_manage(mini, node, mini->here_doc[i].fd);
	if (wait_hds(mini, i) == 42)
		return (42);
	close(mini->here_doc[i].fd[1]);
	return (0);
}

int	here_doc_init(t_main *mini, t_parsing *node, int i)
{
	t_parsing	*nodebis;

	nodebis = node;
	hdinit(mini);
	while (i < mini->hd_count)
	{
		while (nodebis->hdc == 0)
			nodebis = nodebis->next;
		if (nodebis->hdc > 1)
		{
			if (first_hds(mini, nodebis, node) == 42)
				return (42);
		}
		pipe(mini->here_doc[i].fd);
		mini->here_doc[i].pos = 1;
		if (hdc_process(mini, nodebis, i) == 42)
		{
			close(mini->here_doc[i].fd[1]);
			return (42);
		}
		i++;
		nodebis = nodebis->next;
	}
	signal(SIGINT, handle_sig);
	return (0);
}