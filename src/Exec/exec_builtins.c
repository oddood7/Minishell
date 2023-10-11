
#include "../../include/minishell.h"

int	first_builtins2(t_main *mini, t_parsing *node, int len)
{
	if (!ft_strncmp(node->cmd_tab[0], "unset", len) && node->next == NULL
		&& len == 5)
	{
		ft_unset(mini, node, &mini->env_list);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "export", len) && node->next == NULL
		&& len == 6)
	{
		ft_export(mini, node);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "cd", len) && node->next == NULL
		&& len == 2)
	{
		if (mini->pipe_count)
			return (0);
		ft_cd(mini, node);
		return (1);
	}
	return (0);
}

int	first_builtins(t_main *mini, t_parsing *node)
{
	int	len;

	node->incr = 0;
	if (node->cmd_tab[0])
		len = ft_strlen(node->cmd_tab[0]);
	if (node->cmd_tab[0] == NULL)
		return (0);
	if (first_builtins2(mini, node, len))
		return (1);
	if (!ft_strncmp(node->cmd_tab[0], "exit", len) && len == 4)
	{
		if (mini->pipe_count)
			return (0);
		// mini->shell.error = built_exit(mini, node);
		ft_exit(mini, node);
		return (1);
	}
	return (0);
}
