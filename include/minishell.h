/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:55:40 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 17:17:28 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/libftprintf/libftprintf.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

/***** GLOBAL VARIABLE *****/

extern int	g_error;

//////////GARBAGE//////////

typedef struct s_garbage_lst
{
	void					*pointer;
	struct s_garbage_lst	*next;
}					t_garbage_lst;

typedef struct s_garbage
{
	int				len_of_lst;
	t_garbage_lst	*head;
	t_garbage_lst	*tail;
}					t_garbage;

///////////////////////////

typedef struct s_shell
{
	int		is_work;
	int		error;
	char	*home;
	char	*pwd;
	char	*is_pwd;
	char	*user;
	char	*is_oldpwd;
	char	*oldpwd;
	char	*path;
	char	*shlvl;
	char	**cmd_paths;
	char	**input;
	char	*input_bis;
}					t_shell;

typedef struct s_here_doc
{
	int		fd[2];
	int		pos;
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
	int				i;
	char			*str;
	t_operateurs	operateur;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_main
{
	int					ok;
	int					pid_last;
	int					pipe_count;
	int					syntaxe_check;
	int					return_value;
	int					hd_count;
	int					hd_pos;
	int					*pipe_fd;
	char				*path;
	char				*input_line;
	char				*test;
	char				**env;
	char				**env_exp;
	char				**hidetab;
	char				**tab_input_blank;
	char				**cmd_paths;
	t_shell				shell;
	t_lexer				*lexer_list;
	t_lexer				*env_list;
	struct s_parsing	*cmd_parse;
	struct s_here_doc	*here_doc;

}						t_main;

typedef struct s_parsing
{
	int					incr;
	int					num_redirection;
	int					hd_check;
	int					hdc;
	int					doubl;
	int					single;
	char				*hd_file_name;
	char				**cmd_tab;
	t_lexer				*redirection;
	struct s_parsing	*next;
	struct s_parsing	*prev;
}						t_parsing;

typedef struct s_parsermain
{
	int						num_redir;
	t_lexer					*lexer_list;
	t_lexer					*redirection;
	struct s_main			*data;
}							t_parsermain;

////////////////////////////////////////////////////////
/********************* MAIN CODE **********************/

/***** MAIN *****/

int				start_in_loop(t_main *mini, char *input);
int				main(int ac, char **av, char **env);
int				handle_env(t_main *mini);
char			*get_env_var(const char *name);
char			*prompt_cmd(t_shell *shell, char *user);
void			init_main(t_main *mini);
void			mini_loop(t_main *mini);
void			handle_quote_n_expand(t_main *mini);

/***** SIGNAL *****/

void			signal_handler(int sig);
void			sig_init(void);
void			handle_eot(t_main *mini);

/***** LEXER *****/

int				do_lexer(t_main *mini);
int				add_operateur(t_main *mini, char *str, int i, t_lexer **list);
int				word_add_list(t_main *mini, char *str, int i, t_lexer **list);
int				ft_listadd(t_main *mini, char *str, t_operateurs operateur, \
				t_lexer **lst);
int				count_double_quote(char *str, int i);
int				count_single_quote(char *str, int i);
int				different_get_to_quote(char *str, int i, int j);
int				get_to_quote(char *str, int i);
int				get_word_quote(char *str, int i, int j, int quote);
int				add_w_dig(char *str, int i, int j);
char			*ft_trim_space(char const *s);
char			*trim_whitespace(char *str);
void			ft_delid(t_lexer **list, int id);
void			ft_delfirst(t_lexer **lst);
void			ft_lstaddback(t_lexer **lst, t_lexer *new);
void			clean_lexed_list(t_lexer **list);
t_lexer			*ft_delone(t_lexer **lst);
t_lexer			*new_lexer(t_main *mini, char *str, int operateur);
t_operateurs	is_ope(int c);

/**** ERRORS *****/

int				handle_error_bis(int code_err);
int				directory_err(t_main *mini, char *str, int ok);
int				ft_perror(void);
int				error_quote2(t_main *mini, char *str, int sep);
int				error_quote(t_main *mini, char *str, int sep1, int sep2);
void			code_error(int code);
void			err_mall(t_main *mini);

/***** UTILS *****/

int				len_targs(t_lexer *list);
int				ft_strlen_double(char **str);
int				is_numeric(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdupto_n(char *str, char c);
char			*ft_strdup_from(char *str, char c);
char			*from_end_to_char(char *str, char c);
char			**ft_sort(t_lexer **env_list);
char			*ft_long_itoa(long long int n);
char			**env_to_char(t_lexer **env_list);
long long int	ft_long_atoi(const char *nptr);

int				is_rchar(char c, char v);
int				ft_size_list(t_lexer *list);
int				quote_tab(t_parsing *node, int i, int j);
int				nothing_tab(char **tab);
int				check_qt(char *s);
int				ft_whitespace(char c);
int				tab_len(t_parsing *node, int sizetab, int i);
int				check_space(char *str);
int				main_space(char *str);
char			*parse_dup(t_parsing *node, int sizetab, int ok, char *str);
void			resets(t_main *mini);

/***** ENV *****/

int				var_copy(t_main *mini, char *tmp, int i);
int				print_env_exp(t_main *mini);
int				shlvl_err(char *str);
char			*value_env_var(t_main *mini, char *str);
char			*find_var_env(char **env, char *var);
char			*get_var_name(char *str, t_main *mini);
void			do_shlvl(t_main *mini, char **env);
void			env_export_cpy(t_main *mini, char *decla);
void			get_env(t_main *mini, char **env);
void			get_env_export(t_main *mini);
void			change_var_value(t_main *mini, char *new, char *old);

/***** PARSING *****/

int				parsing(t_main *mini);
int				var_check(t_main *mini, t_lexer *list);
int				dir_file_check(t_main *mini, char *str);
int				finding_var(t_main *mini, char *str, int len);
int				count_lex(t_lexer *list);
int				rm_quote(t_main *mini, t_parsing *node, int i, int quote);
int				quotes(t_main *mini, t_parsing *node, int i);
int				check_set(char c, int quote);
int				left_check(t_main *mini, t_lexer *ope);
int				right_check(t_main *mini, t_lexer *ope);
int				pipe_check(t_main *mini, t_lexer *ope);
int				left2_check(t_main *data, t_lexer *ope);
int				right2_check(t_main *data, t_lexer *ope);
int				single_handle(t_main *mini, t_lexer *ongoing);
int				double_handle(t_main *mini, t_lexer *ongoing);
int				operateur_handle(t_main *mini);
int				weird_check(t_main *mini, char *str);
int				check_all(t_main *mini);
int				err_syn(t_main *mini, char *str);
int				two_pipes(t_main *mini, t_lexer *ongoing);
int				slash_manage(t_main *mini, char *str);
int				string_syn(t_main *mini, char *str);
int				string_syn_plus(t_main *mini, char *str, int i);
int				string_syn2(t_main *mini, t_lexer *ongoing);
int				syntax_check(t_main *mini, int size);
int				count_quotes(char *str, int quote);
int				find_built(char *str);
char			*malloc_space(t_main *mini, t_parsing *node, int i);
char			*check_4_strim(t_main *mini, t_parsing *node, int i, \
				int quote);
char			*ft_trim(t_main *mini, char const *s1, int quote);
char			*cpquote(t_main *mini, char *s, int j, int quote);
char			*rm_quote_redir(t_main *mini, char *s, int quote, int j);
void			init_parser_data(t_parsermain *data, t_lexer *list, \
				t_main *mini);
void			input_redir(t_main *mini, t_lexer *tmp, t_parsermain *data);
void			redirections(t_main *mini, t_parsermain *data);
void			parse_addback(t_parsing **lst, t_parsing *new);
void			check_quote_redir(t_main *mini, t_lexer *node);
void			parsing_tab_help(t_main *mini, t_parsing *node, int i, \
				int len);
void			check_tab(t_main *mini);
void			built_move(t_parsing *node, size_t j);
t_parsing		*init_cmd(t_main *mini, t_parsermain *data, int n_word);
t_parsing		*parse_new(t_main *mini, char **tab, int redir, t_lexer *red);

/***** EXPANDER *****/

int				expander_doll(t_main *mini, t_parsing *node, int i, int j);
int				get_rv(t_main *mini, t_parsing *node, int i, int j);
int				expanding_bis(t_main *mini, t_parsing *node, int i, int j);
int				second_expand(t_main *mini, t_parsing *node, int i, int j);
int				copy_bis(char *s1, char *s2, int i, int ok);
int				copy_past(t_parsing *cmd_node, int i, int j_dol, \
				char *str_replace);
int				check_env_bis_qt(char **env, char *str_dol);
int				check_env_variable_qt(t_main *mini, char *s, int j);
int				expand_dol_qt(t_main *mini, t_parsing *node, int i, int j);
int				rm_dollard(t_main *mini, t_parsing *node, int i, int j);
int				while_dol(t_main *mini, t_parsing *node, int i, int dol);
int				check_env_var(t_main *mini, char *s, int j);
int				check_env_bis(char **env, char *dollar);
char			*add_qt(t_main *mini, char *s);
char			*keep_good_str_qt(char **env, int nb_env);
char			*copy_without_dol(t_parsing *node, int i, int j, char *s);
char			*check_char_after(t_parsing *node, int i, int j_dol);
char			*just_alloc(int len, int j_dol, char *s_af);
char			*keep_good_str(char **env, int nb_env);
char			*go_itoa_replace(t_main *data, char *s);
void			expanding(t_main *mini, t_parsing *node, int i, int j);

/***** BUILTINS *****/

//Bultins
int				ft_echo(t_main *mini, t_parsing *parse);
int				ft_cd(t_main *mini, t_parsing *parse);
int				ft_pwd(t_main *mini);
int				ft_env(t_main *mini, t_parsing *parse, t_lexer **env_list);
int				ft_unset(t_main *mini, t_parsing *parse, t_lexer **env_list);
int				ft_export(t_main *mini, t_parsing *parse);
int				ft_exit(t_main *mini, t_parsing *parse);

//Builtins Utils
int				all_cmd(t_lexer *arg, t_shell *shell, t_main **list, \
				t_lexer **env_list);
int				cd_move_and_change(t_main *mini);
int				cd_real_version(char *buf, t_main *mini, t_parsing *parse);
int				change_env_exp(t_lexer **env_list, char *name_env, \
				char *value);
int				parse_export(char *str);
int				searchin_env(t_lexer **env_list, char *str);
int				set_env(t_main *mini, char **env);
int				ft_plus_shell(t_main *mini);
int				export_out_main(t_main *mini);
void			change_env_cd(t_lexer **env_list, char *new_str, \
				char *change_value);
void			add_env(t_lexer **env_list, char *str);
void			shell_change(t_shell *shell, char *str, char *value);

/***** EXEC *****/

int				last_redir(t_main *mini, t_parsing *node, int *in, int *out);
int				first_builtins(t_main *mini, t_parsing *node);
int				first_builtins2(t_main *mini, t_parsing *node, int len);
int				close_error(int in, int out);
int				lstsize(t_parsing *lst);
int				contains_char(char *str, char c);
int				open_outfile(t_main *mini, t_parsing *node, int old_fd);
int				open_infile(t_main *mini, t_parsing *node, int old_fd);
int				open_append(t_main *mini, t_parsing *node, int old_fd);
int				redir_pipe(t_main *mini, t_parsing *node, int *in, int *out);
int				last_redir2(t_main *mini, t_parsing *node, int *in, int *out);
char			*get_command(t_main *mini, char **paths, char *cmd);
char			*find_path(char **envp);
void			find(t_main *mini, t_parsing *node);
void			find_2(t_main *mini, char *cmd, int len);
void			find_3(t_main *mini, char *cmd, int len);
void			free_process(t_main *mini);
void			wait_exec(t_main *mini);
void			exit_error_redir(t_main *mini, int fd[2]);
void			close_pipe(t_main *mini, int count);
void			no_command(t_main *mini, t_parsing *node);
void			print_no_command(t_main *mini, char *s, int i);
void			hdc_init(t_main *mini);
void			first_pinit(t_main *mini);
void			pipe_init(t_main *mini, t_parsing *node);
void			ft_execve(t_main *mini, t_parsing *node, char *cmd);
void			close_hds(t_main *mini, t_parsing *node);
void			exit_access(t_main *mini, char *cmd);
void			redir_pipe0(t_main *mini, t_parsing *node, int *in, int *out);
void			last_redir_hd(t_main *mini, t_parsing *node, int fd);
void			last_redir0(t_main *mini, t_parsing *node, int *in, int *out);
void			ft_dup2close(int fd[2], int check);
void			pipe_work(t_main *mini, int fd[2], t_parsing *node, \
				int old_fd[2]);
void			exec2(t_main *mini, t_parsing *node, char *cmd, int fd[2]);
void			exec(t_main *mini, t_parsing *node, char *cmd);
void			execute_cmd(t_main *mini);
void			init_ex(t_main *mini, int fd[2], int old_fd[2], int *i);
void			last_process(t_main *mini, t_parsing *node, char *cmd, \
				int fd[2]);

/***** HEREDOC *****/

int				first_hds(t_main *mini, t_parsing *node, t_parsing *nodeorg);
int				has_variable(char *input);
int				here_doc_var(t_main *mini, char *input, int i, int fd[2]);
int				return_hd_count(int hd_count);
int				wait_hds(t_main *mini, int i);
int				hdc_process(t_main *mini, t_parsing *node, int i);
int				here_doc_init(t_main *mini, t_parsing *node, int i);
int				init_loop(t_parsing *node, char *input, int fd[2]);
int				ft_varname_len(char *str);
char			*var_hd_name(t_main *mini, char *input);
char			*get_var_content(t_main *mini, char *var_name);
char			*skip_tmpr(t_lexer *tmpr);
void			sig_hd(int signal);
void			close_free_hd(t_main *mini, t_parsing *node, char *input, \
				int check);
void			write_hd(t_main *mini, char *input, int fd[2]);
void			here_doc_manage(t_main *mini, t_parsing *node, int fd[2]);
void			first_hd_manage(t_main *mini, t_parsing *node, char *str);
void			hdinit(t_main *mini);
t_main			*return_free_mini(t_main *mini);
t_here_doc		*return_hd(t_here_doc *here_doc);

/***** GARBAGE *****/

void			garbage_add(void *pointer);
void			free_garbage(void);
void			add_d_t_garbage(void **double_array, int len);
void			malloc_failure(void);
void			*ft_malloc(size_t size);
t_garbage		*start_garbage(void);
t_garbage		*get_garbage(void);
t_garbage_lst	*new_element(void *pointer_to);

/***** TESTS *****/

void			pr(t_lexer *lexer_list);
void			pr_redir(t_lexer *lexer_list);
void			prrr(t_parsing *cmd_parse, int ok);

#endif