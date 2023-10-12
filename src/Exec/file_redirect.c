/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:55:07 by asalic            #+#    #+#             */
/*   Updated: 2023/10/12 18:55:07 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_pipe0(t_main *mini, t_parsing *node, int *in, int *out)
{
	if (node->redirection->operateur == RIGHT)
		*out = open_outfile(mini, node, *out);
	if (node->redirection->operateur == LEFT)
		*in = open_infile(mini, node, *in);
	if (node->redirection->operateur == RIGHT_RIGHT)
		*out = open_append(mini, node, *out);
}

int	redir_pipe(t_main *mini, t_parsing *node, int *in, int *out)
{
	t_lexer	*tmp;

	node->hd_check = 0;
	tmp = node->redirection;
	while (node->redirection)
	{
		redir_pipe0(mini, node, in, out);
		if (node->redirection->operateur == LEFT_LEFT)
		{
			node->hd_check = 1;
			dup2(mini->here_doc[mini->hd_pos].fd[0], 0);
			close(mini->here_doc[mini->hd_pos].fd[0]);
			if (*in > -1)
				close(*in);
		}
		if (*out == -2 || *in == -2)
		{
			node->redirection = tmp;
			return (close_error(*in, *out));
		}
		node->redirection = node->redirection->next;
	}
	node->redirection = tmp;
	return (0);
}

void	last_redir_hd(t_main *mini, t_parsing *node, int fd)
{
	node->hd_check = 1;
	if (fd > -1)
		close(fd);
	dup2(mini->here_doc[mini->hd_pos].fd[0], 0);
	close(mini->here_doc[mini->hd_pos].fd[0]);
}

int	last_redir2(t_main *mini, t_parsing *node, int *in, int *out)
{
	if (node->redirection->operateur == RIGHT_RIGHT)
	{
		*out = open_append(mini, node, *out);
		dup2(*out, 1);
		close(*out);
	}
	if (node->redirection->operateur == LEFT_LEFT)
	{
		if (node->hd_check != 1)
			last_redir_hd(mini, node, *in);
	}
	if (*out == -2 || *in == -2)
		return (close_error(*in, *out));
	return (0);
}

void	last_redir0(t_main *mini, t_parsing *node, int *in, int *out)
{
	if (node->redirection->operateur == RIGHT)
	{
		*out = open_outfile(mini, node, *out);
		if (*out > 1)
		{
			dup2(*out, 1);
			close(*out);
		}
	}
	if (node->redirection->operateur == LEFT)
	{
		*in = open_infile(mini, node, *in);
		if (*in > -1)
		{
			dup2(*in, 0);
			close(*in);
		}
	}
}
