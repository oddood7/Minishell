/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:06:56 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:44:20 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_loop(t_parsing *node, char *input, int fd[2])
{
	int		i;
	size_t	size;
	t_lexer	*tmpr;

	i = 0;
	tmpr = node->redirection;
	while (node->redirection)
	{
		if (node->redirection->operateur == LEFT_LEFT)
			i++;
		if (node->redirection->operateur == LEFT_LEFT && i == node->hdc)
			break ;
		node->redirection = node->redirection->next;
	}
	size = ft_strlen(node->redirection->str);
	if (!ft_strncmp(input, node->redirection->str, size)
		&& size == ft_strlen(input))
	{
		close(fd[1]);
		node->redirection = tmpr;
		return (0);
	}
	node->redirection = tmpr;
	return (1);
}

void	here_doc_manage(t_main *mini, t_parsing *node, int fd[2])
{
	char	*input;
	int		j;

	j = 0;
	signal(SIGINT, sig_hd);
	close(fd[0]);
	while (1)
	{
		input = readline(">");
		if (!input)
			close_free_hd(mini, node, input, j);
		if (!init_loop(node, input, fd))
			close_free_hd(mini, node, input, -42);
		write_hd(mini, input, fd);
		j++;
	}
}

void	first_hd_manage(t_main *mini, t_parsing *node, char *str)
{
	char	*input;
	size_t	len;

	len = ft_strlen(str);
	signal(SIGINT, sig_hd);
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			printf("bash: warning: here-document at line 1");
			printf("deliminited by end-of-file");
			printf("(wanted `%s')\n", str);
			close_free_hd(mini, node, input, -42);
			free_garbage();
			exit(1);
		}
		if (!ft_strncmp(input, str, len) && len == ft_strlen(input))
		{
			close_free_hd(mini, node, input, -42);
			free_garbage();
			exit(1);
		}
	}
}

int	first_hds(t_main *mini, t_parsing *node, t_parsing *nodeorg)
{
	int		pid;
	int		i;
	int		status;
	t_lexer	*tmpr;
	char	*str;

	tmpr = node->redirection;
	i = 1;
	while (i < node->hdc)
	{
		while (tmpr->operateur != LEFT_LEFT)
			tmpr = tmpr->next;
		str = tmpr->str;
		tmpr = tmpr->next;
		pid = fork();
		if (pid == 0)
			first_hd_manage(mini, nodeorg, str);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 42)
			return (42);
		i++;
	}
	return (0);
}

void	hdinit(t_main *mini)
{
	return_free_mini(mini);
	return_hd(mini->here_doc);
	return_hd_count(mini->hd_count);
	signal(SIGINT, SIG_IGN);
}
