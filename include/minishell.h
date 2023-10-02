/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:55:40 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/03 00:14:18 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>


typedef struct s_here_doc
{
	int fd[2];
	int pos;
}				t_here_doc;

typedef enum s_operateurs
{
    DEFAULT,
    PIPE,
    RIGHT,
    RIGHT_RIGHT,
    LEFT,
    LEFT_LEFT,
}				t_operateurs;

typedef struct s_lexer
{
    char                *str;
    t_operateurs		operateur;
    int                    i;
    struct s_lexer        *next;
    struct s_lexer        *prev;
}                        t_lexer;

typedef	struct s_list
{
	char	*var;
	struct s_list	*next;
}					t_list;

typedef struct s_main
{
    int                    ok;
    int                    pid_last;
    char                *input_line;
    int                    pipe_count;
    t_lexer                *lexer_list;
    struct s_parsing    *cmd_parse;
    char                	**env;
    char                **env_exp;
    char                **hidetab;
    int                    return_value;
    int                    hd_count;
    int                    hd_pos;
	struct s_here_doc		*here_doc;
    char                **tab_input_blank;
    int                    *pipe_fd;
    char                *path;
    char                **cmd_paths;
    char                *test;
    int                    syntaxe_check;
}                        t_main;

typedef struct s_parsing
{
    char                **cmd_tab;
    int                    (*builtin)(t_main *, struct s_parsing *);
    int                    num_redirection;
	char				*hd_file_name;
    t_lexer                *redirection;
	int						hd_check;
	int						hdc;
    int                    doubl;
    int                    single;
    struct s_parsing    *next;
    struct s_parsing   *prev;
}                        t_parsing;

typedef struct s_parsermain
{
    t_lexer                *lexer_list;
    t_lexer                *redirection;
    int                    num_redir;
    struct s_main        *data;
}                        t_parsermain;

/*****MAIN*****/

int init_minishell(t_main *mini, char *str);
void main_loop(t_main *minishell);
int main(int ac, char **av, char **env);

/*****LEXER*****/

int	do_lexer(t_main *mini);
int	add_operateur(t_main *mini, char *str, int i, t_lexer **list);
t_operateurs	is_ope(int c);
int	word_add_list(t_main *mini, char *str, int i, t_lexer **list);
int	ft_listadd(t_main *mini, char *str, t_operateurs operateur, t_lexer **lst);
t_lexer	*new_lexer(t_main *mini, char *str, int operateur);
int    count_double_quote(char *str, int i);
int    count_single_quote(char *str, int i);
int    different_get_to_quote(char *str, int i, int j);
int    get_to_quote(char *str, int i);
int	get_word_quote(char *str, int i, int j, int quote);
int    add_w_dig(char *str, int i, int j);
void	ft_delid(t_lexer **list, int id);
void	ft_delfirst(t_lexer **lst);
void	ft_lstaddback(t_lexer **lst, t_lexer *new);
t_lexer *ft_delone(t_lexer **lst);

/****UTILS&ERRORS*****/

int	ft_whitespace(char c);
void ft_free_tab(char **tab);
void   ft_free_lexer(t_lexer *list);
void    free_cmd_tab(t_main *mini);
void    free_cmd_lst(t_parsing *lst);
void	err_mall(t_main *mini);
int		directory_err(t_main *mini, char *str, int ok);
int		handle_error(t_main *mini, char *str, int rv);
int		is_rchar(char c, char v);
int 	ft_size_list(t_lexer *list);

/*****ENV*****/

t_list	*get_env_list(char **env);
void get_env_tab(t_list *env, t_main *mini);
int    dup_env(t_main *mini, char *tmp, int i);
void	get_env_export(t_main *mini);
void	env_export2(t_main *mini, char *add);

/*****PARSING*****/

int parsing(t_main *mini);
t_parsing	*init_cmd(t_main *mini, t_parsermain *data, int n_word);
t_parsing *parse_new(t_main *mini, char **tab, int redir, t_lexer *red);
void	parse_addback(t_parsing **lst, t_parsing *new);
int	count_lex(t_lexer *list);
t_parsermain	init_parser_data(t_lexer *list, t_main *mini);
void	input_redir(t_main *mini, t_lexer *tmp, t_parsermain *data);
void	redirections(t_main *mini, t_parsermain *data);
int		left_check(t_main *mini, t_lexer *ope);
int    right_check(t_main *mini, t_lexer *ope);
int		pipe_check(t_main *mini, t_lexer *ope);
int    left2_check(t_main *data, t_lexer *ope);
int    right2_check(t_main *data, t_lexer *ope);
int		single_handle(t_main *mini, t_lexer *ongoing);
int		double_handle(t_main *mini, t_lexer *ongoing);
int		operateur_handle(t_main *mini);
int 	weird_check(t_main *mini, char *str);
int 	check_all(t_main *mini);
int		err_syn(t_main *mini, char *str);
int		two_pipes(t_main *mini, t_lexer *ongoing);
int		slash_manage(t_main *mini, char *str);
int		string_syn(t_main *mini, char *str);
int		string_syn_plus(t_main *mini, char *str, int i);
int    	string_syn2(t_main *mini, t_lexer *ongoing);
int    syntax_check(t_main *mini, int size);
char    *malloc_space(t_main *mini, t_parsing *node, int i);
int    count_quotes(char *str, int quote);
char    *check_4_strim(t_main *mini, t_parsing *node, int i, int quote);
int    rm_quote(t_main *mini, t_parsing *node, int i, int quote);
int    quotes(t_main *mini, t_parsing *node, int i);
int    check_set(char c, int quote);
char    *ft_trim(t_main *mini, char const *s1, int quote);
char    *cpquote(t_main *mini, char *s, int j, int quote);
char    *rm_quote_redir(t_main *mini, char *s, int quote, int j);
void    check_quote_redir(t_main *mini, t_lexer *node);


/*****BUILTINS*****/

void env_pwd_exec(t_main *mini, t_parsing *parse);
int	env_builtin(t_main *mini);
int		pwd_builtin(t_main *mini, t_parsing *parse);
int	n_check(char *str);
void	print_echo(char **tab, int j);
int	echo_builtin(t_main *mini, t_parsing *parse);
int	exit_builtin(t_main *mini, t_parsing *parse);
int	stop_arguments(char **tab, int i);