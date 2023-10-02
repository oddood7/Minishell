#include "../../include/minishell.h"

void	free_process(t_main *mini)
{
	int	i;

	i = 0;
	if (mini->hd_count)
	{
		while (i < mini->hd_count)
		{
			if (mini->here_doc[i].fd[0] > -1)
				close(mini->here_doc[i].fd[0]);
			i++;
		}
		free(mini->here_doc);
	}
	if (mini->cmd_paths)
		free_tab(mini->cmd_paths);
}

void	wait_exec(t_main *mini)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(mini->pid_last, &status, 0);
	while (i < mini->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	signal(SIGINT, sig_handler);
	if (WIFEXITED(status))
		mini->return_value = WEXITSTATUS(status);
}

void	exit_error_redir(t_main *mini, int fd[2])
{
	if (fd[0] > 1)
		close (fd[0]);
	if (fd[1] > 1)
		close(fd[1]);
	reset_stuff(mini);
	exit (1);
}

void	built_in_free(t_main *mini)
{
	free_tab(mini->cmd_paths);
	free_tab(mini->env);
	free_tab(mini->env_exp);
	if (mini->here_doc)
		free(mini->here_doc);
	resets(mini);
}

int	close_error(int in, int out)
{
	if (in > 1)
		close (in);
	if (out > 1)
		close (out);
	return (-2);
}
