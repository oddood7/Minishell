#include "../../include/minishell.h"


void	find_3(t_main *mini, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "unset", len) && len == 5)
	{
		ft_unset(mini->lexer_list, &mini->shell, mini->env_list);
		built_in_free(mini);
		exit(mini->return_value);
	}
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
	{
		ft_echo(mini, mini->cmd_parse);
		built_in_free(mini);
		exit (mini->return_value);
	}
}

void	find_2(t_main *mini, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "exit", len) && len == 4)
	{
		built_in_free(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
	{
		ft_export(mini->lexer_list, &mini->shell, &mini->env_list);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
	{
		ft_pwd(&mini->shell, &mini->env_list);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else
		find_3(mini, cmd, len);
}

void	find(t_main *mini, t_parsing *node)
{
	char	*cmd;
	int		len;
	char	*cleaned_cmd;

	if (node->cmd_tab[0] == NULL)
		return ;
	cmd = node->cmd_tab[0];
	cleaned_cmd = ft_strtrim(cmd, " ");
	len = ft_strlen(cleaned_cmd);
	if (!ft_strncmp(cleaned_cmd, "cd", len) && len == 2)
	{
		ft_cd(mini, mini->cmd_parse);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cleaned_cmd, "env", len) && len == 3)
	{
		ft_env(mini, mini->cmd_parse, &mini->env_list);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else
		find_2(mini, cleaned_cmd, len);
	free(cleaned_cmd);
}