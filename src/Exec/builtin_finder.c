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
	/* else if (!ft_strncmp(cmd, "export", len) && len == 6)
	{
		built_export(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	} */
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
	{
		built_pwd(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else
		find_3(mini, node, cmd, len);
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
		printf("About to call built_cd\n");
		built_cd(mini, node);
		built_in_free(mini);
		printf("Finished calling built_cd\n");
		exit (mini->return_value);
	}
	else if (!ft_strncmp(cleaned_cmd, "env", len) && len == 3)
	{
		built_env(mini, node);
		built_in_free(mini);
		exit (mini->return_value);
	}
	else
		find_2(mini, node, cleaned_cmd, len);
	free(cleaned_cmd);
}