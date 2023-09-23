/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:55:40 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/22 15:56:57 by lde-mais         ###   ########.fr       */
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

typedef struct s_here_doc
{
    int                    fd[2];
    int                    pos;
}                        t_here_doc;

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
    char                **env_bis;
    char                **env_exp;
    char                **hidetab;
    int                    return_value;
    int                    hd_count;
    int                    hd_pos;
    t_here_doc            *here_doc;
    char                **tab_input_blank;
    int                    *pipe_fd;
    char                *path;
    char                **cmd_paths;
    char                *test;
    int                    syntaxe_check;
}                        t_main;

typedef struct s_cmd_parse
{
    char                **cmd_tab;
    int                    (*builtin)(t_main *, struct s_cmd_parse *);
    int                    num_redirection;
    char                *hd_file_name;
    t_lexer                *redirection;
    int                    hd_check;
    int                    hdc;
    int                    d_qt;
    int                    s_qt;
    struct s_cmd_parse    *next;
    struct s_cmd_parse    *prev;
}                        t_cmd_parse;

typedef struct s_parser_data
{
    t_lexer                *lexer_list;
    t_lexer                *redirection;
    int                    num_redir;
    struct s_main        *data;
}                        t_parser_data;