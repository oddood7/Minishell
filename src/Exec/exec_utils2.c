#include "../../include/minishell.h"

void	no_command(t_main *mini, t_parsing *node)
{
	int	i;

	i = 0;
	if (!node->redirection)
		print_no_command(mini, node->cmd_tab[0], 0);
	ft_free_tab(mini->cmd_paths);
	ft_free_tab(mini->env);
	ft_free_tab(mini->env_exp);
	resets(mini);
	while (i < mini->hd_count)
	{
		if (mini->here_doc[i].fd[0] > -1)
			close(mini->here_doc[i].fd[0]);
		if (mini->here_doc[i].fd[0] > -1)
			close(mini->here_doc[i].fd[1]);
		i++;
	}
	if (mini->here_doc)
		free(mini->here_doc);
	exit(127);
}

void	hdc_init(t_main *mini)
{
	int	i;

	i = 0;
	if (mini->hd_count)
	{
		mini->here_doc = malloc(sizeof(t_here_doc) * mini->hd_count);
		if (!mini->here_doc)
			err_mall(mini);
		while (i < mini->hd_count)
		{
			mini->here_doc[i].pos = 0;
			i++;
		}
	}
}

void	first_pinit(t_main *mini)
{
	mini->cmd_paths = NULL;
	mini->path = find_path(mini->env);
	mini->cmd_paths = ft_split(mini->path, ':');
	mini->hd_count = 0;
	mini->here_doc = NULL;
}

void	pipe_init(t_main *mini, t_parsing *node)
{
	t_parsing	*tmp;
	t_lexer		*tmpr;

	first_pinit(mini);
	tmp = node;
	while (tmp)
	{
		tmp->hdc = 0;
		if (tmp->redirection)
		{
			tmpr = tmp->redirection;
			while (tmpr)
			{
				if (tmpr->operateur == LEFT_LEFT)
					tmp->hdc++;
				tmpr = tmpr->next;
			}
			if (tmp->hdc)
				mini->hd_count++;
		}
		tmp = tmp->next;
	}
	hdc_init(mini);
}

void	ft_execve(t_main *mini, t_parsing *node, char *cmd)
{
	if (cmd == NULL)
		no_command(mini, node);
	execve(cmd, node->cmd_tab, mini->env);
	ft_free_tab(mini->cmd_paths);
	ft_free_tab(mini->env);
	ft_free_tab(mini->env_exp);
	resets(mini);
	exit(1);
}
