/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:52:48 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 15:10:14 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    handle_quote_n_expand(t_main *mini)
{
    t_parsing   *node;
    int            i;

    node = mini->cmd_parse;
    while (node)
    {
        i = 0;
        while (node->cmd_tab[i])
        {
            node->doubl = count_quotes(node->cmd_tab[i], 34);
            node->single = count_quotes(node->cmd_tab[i], 39);
            if (!quotes(mini, node, i))
                expanding(mini, node, i, 0);
            i++;
        }
        node = node->next;
    }
}

int    start_in_loop(t_main *mini, char *input)
{
    mini->input_line = ft_malloc(sizeof(char) * (ft_strlen(input) + 1));
    if (!mini->input_line)
        err_mall(mini);
    ft_strlcpy(mini->input_line, input, ft_strlen(input));
    if (!do_lexer(mini))
		main_space("lexer failed.");
    mini->cmd_parse = NULL;
    if (!parsing(mini))
    {
        mini->syntaxe_check = 1;
        return (1);
    }
    handle_quote_n_expand(mini);
    check_tab(mini);
    return (0);
}

static int	handle_history(t_main *mini, int bool, char *input)
{
	if (bool == 1 && !(ft_strcmp(mini->shell.input_bis, input) == 0 \
	&& ft_strlen(mini->shell.input_bis) == ft_strlen(input)))
        add_history(input);
	else if (bool == 0)
	{
		add_history(input);
		bool = 1;
	}
	mini->shell.input_bis = ft_strdup(input);
	if (! mini->shell.input_bis)
		return (2);
	return (bool);
}

void    mini_loop(t_main *mini)
{
    char    *input;
    char    *prompt_char;
    int		bool;

	bool = 0;
    while (42)
    {
        prompt_char = prompt_cmd(&mini->shell, mini->shell.user);
        input = readline(prompt_char);
        if (!input)
            handle_eot(mini);
        if (g_error != 0)
	    {
	    	mini->shell.error = g_error;
	    	g_error = 0;
	    }
        if (check_space(input) && !error_quote(mini, input, 34, 39))
        {
            if (input[0] != '\0')
            {
                if (!start_in_loop(mini, input))
                    execute_cmd(mini);
            }
        }
        bool = handle_history(mini, bool, input);
		if  (bool == 2)
			return ;
        // free(input);
    }
    rl_clear_history();

}

int    main(int ac, char **av, char **env)
{
    t_main		mini;

    (void)av;
	start_garbage();
    if (ac != 1)
        return (main_space("run ./minishell without arg"));
    if (!env[0])
        return (main_space("env is missing"));
    init_main(&mini);
    get_env(&mini, env);
    do_shlvl(&mini, mini.env);
    mini_loop(&mini);
    ft_printf("out !\n");
    free_garbage();
    return (0);
}