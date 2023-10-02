#include "../../include/minishell.h"

int	lstsize(t_parsing *lst)
{
	int			size;
	t_parsing	*lsts;

	lsts = lst;
	size = 0;
	while (lsts != NULL)
	{
		lsts = lsts->next;
		size++;
	}
	return (size);
}

int	contains_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_command(t_main *mini, char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	if (!paths || !cmd || !cmd[0])
		return (NULL);
	if (contains_char(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		if (access(cmd, X_OK))
			exit_access(mini, cmd);
		return (NULL);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			return (envp[i] + 5);
		i++;
	}
	return (" ");
}

void	close_pipe(t_main *mini, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (mini->pipe_fd[i] > -1)
			close(mini->pipe_fd[i]);
		i++;
	}
}
