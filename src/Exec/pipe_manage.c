#include "../../include/minishell.h"

void	ft_dup2close(int fd[2], int check)
{
	if (!check)
	{
		if (fd[1] != 1)
		{
			if (fd[0] > -1)
				close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		return ;
	}
	else
	{
		if (fd[0] != -1)
			close(fd[0]);
		return ;
	}
}

void	pipe_work(t_main *mini, int fd[2], t_parsing *node, int old_fd[2])
{
	pid_t	pid;
	char	*cmd;

	pid = fork();
	cmd = NULL;
	if (pid == 0)
	{
		close_hds(mini, node);
		if (redir_pipe(mini, node, &old_fd[0], &fd[1]) == -2)
			exit_error_redir(mini, fd);
		if (old_fd[0] != -1 && node->hd_check == 0)
		{
			dup2(old_fd[0], 0);
			close(old_fd[0]);
		}
		ft_dup2close(fd, 0);
		find(mini, node);
		cmd = get_command(mini, mini->cmd_paths, node->cmd_tab[0]);
		if (cmd == NULL)
			ft_dup2close(old_fd, 1);
		if (cmd == NULL)
			close(fd[0]);
		ft_execve(mini, node, cmd);
	}
	ft_dup2close(old_fd, 1);
}

void	exec2(t_main *mini, t_parsing *node, char *cmd, int fd[2])
{
	mini->pid_last = fork();
	if (mini->pid_last == 0)
		last_process(mini, node, cmd, fd);
	if (mini->pipe_count)
	{
		close(fd[1]);
		close(fd[0]);
	}
}

void	exec(t_main *mini, t_parsing *node, char *cmd)
{
	int		i;
	int		fd[2];
	int		old_fd[2];

	init_ex(mini, fd, old_fd, &i);
	while (i < mini->pipe_count)
	{
		pipe(fd);
		node->hd_check = 0;
		pipe_work(mini, fd, node, old_fd);
		if (old_fd[0] != -1)
			close(old_fd[0]);
		if (node->hdc)
			mini->hd_pos++;
		old_fd[0] = fd[0];
		old_fd[1] = fd[1];
		close(fd[1]);
		node = node->next;
		i++;
	}
	exec2(mini, node, cmd, fd);
}

void	execute_cmd(t_main *mini)
{
	t_parsing	*node;
	char		*cmd;

	cmd = NULL;
	node = mini->cmd_parse;
	mini->pipe_count = lstsize(node) - 1;
	if (first_builtins(mini, node))
		return ;
	pipe_init(mini, node);
	/* if (here_doc_init(mini, node, 0) == 42)
	{
		ft_free_tab(mini->cmd_paths);
		free(mini->here_doc);
		mini->return_value = 130;
		return ;
	} */
	exec(mini, node, cmd);
	wait_exec(mini);
	free_process(mini);
}
