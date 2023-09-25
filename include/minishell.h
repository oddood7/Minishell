/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:55:40 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/23 19:42:02 by lde-mais         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

typedef enum s_operateurs
{
    DEFAULT,
    PIPE,
    RIGHT,
    RIGHT_RIGHT,
    LEFT,
    LEFT_LEFT,
}                        t_operateurs;

typedef struct s_lexer
{
    char                *str;
    t_operateurs        operateur;
    int                    i;
    struct s_lexer        *next;
    struct s_lexer        *prev;
}                        t_lexer;

typedef struct s_main
{
    int                    ok;
    int                    pid_last;
    char                *input_line;
    int                    pipe_count;
    t_lexer                *lexer_list;
    struct s_cmd_parse    *cmd_parse;
    char                	**env;
    char                **env_exp;
    char                **hidetab;
    int                    return_value;
    int                    hd_count;
    int                    hd_pos;
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
    int                    (*builtin)(t_main *, struct s_cmd_parse *);
    int                    num_redirection;
    t_lexer                *redirection;
    int                    doubl;
    int                    single;
    struct s_cmd_parse    *next;
    struct s_cmd_parse    *prev;
}                        t_parsing;

typedef struct s_parser_data
{
    t_lexer                *lexer_list;
    t_lexer                *redirection;
    int                    num_redir;
    struct s_main        *data;
}                        t_parser_data;

/*****MAIN*****/

int init_minishell(t_main *mini, char *str);
void main_loop(t_main *minishell);
int main(int ac, char **av);

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

/****UTILS*****/

int	ft_whitespace(char c);

/*****PARSING*****/

int parsing(t_main *mini);
t_parsing	*init_cmd(t_main *mini, t_parser_data *data, int n_word);
t_parsing *parse_new(t_main *mini, char **tab, int redir, t_lexer *red);
void	parse_addback(t_parsing **lst, t_parsing *new);
int	count_lex(t_lexer *list);