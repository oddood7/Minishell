#include "../../include/minishell.h"

/* Prompt: $USER:$PWD>
 * Je pourrais mettre des couleurs si tu veux que ca ressorte mieux
*/
char	*prompt_cmd(t_shell *shell, char *user)
{
	char	*prompt;
	char	*username;
	char	*pwd;

	prompt = NULL;
	username = NULL;
	pwd = NULL;
	if (user != NULL)
		username = ft_strjoin(user, ":");
	if (shell->is_pwd != NULL)
		pwd = ft_strjoin(username, shell->is_pwd);
	prompt = ft_strjoin(pwd, ">");
	free(username);
	free(pwd);
	return (prompt);
}
