#include "../../include/minishell.h"


void	find_3(t_main *mini, t_parsing *node, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "unset", len) && len == 5)
	{
		built_unset(mini, node);
		built_in_free(mini);
		exit(mini->return_value);
	}
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
	{
		built_echo(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
}

void	find_2(t_main *mini, t_parsing *node, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "exit", len) && len == 4)
	{
		built_in_free(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
	{
		built_export(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
	{
		built_pwd(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else
		finder_3(mini, node, cmd, len);
}

void	find(t_main *mini, t_parsing *node)
{
	char	*cmd;
	int		len;

	if (node->cmd_tab[0] == NULL)
		return ;
	cmd = node->cmd_tab[0];
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", len) && len == 2)
	{
		built_cd(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
	{
		built_env(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else
		finder_2(mini, node, cmd, len);
}