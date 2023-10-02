
#include "../../include/minishell.h"

int	first_builtins2(t_main *mini, t_parsing *node, int len)
{
	if (mini->pipe_count == 0 && contains_char(node->cmd_tab[0], '=')
		&& node->cmd_tab[0][0] != '=')
	{
		add_v_to_hidetab(mini, node->cmd_tab[0]);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "unset", len) && node->next == NULL
		&& len == 5)
		return (built_unset(mini, node));
	if (!ft_strncmp(node->cmd_tab[0], "export", len) && node->next == NULL
		&& len == 6)
		return (built_export(mini, node));
	if (!ft_strncmp(node->cmd_tab[0], "cd", len) && node->next == NULL
		&& len == 2)
	{
		if (mini->pipe_count)
			return (0);
		return (built_cd(mini, node));
	}
	return (0);
}

int	first_builtins(t_main *mini, t_parsing *node)
{
	int	len;

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
		mini->return_value = built_exit(mini, node);
		return (1);
	}
	return (0);
}
