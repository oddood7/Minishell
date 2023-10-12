# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 15:58:12 by lde-mais          #+#    #+#              #
#    Updated: 2023/10/12 14:32:00 by lde-mais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_PATH = include/libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC = ./src/Program/main.c \
	./src/Program/env.c \
	./src/Program/env_utils.c \
	./src/Program/signal.c \
	./src/Program/shlvl.c \
	./src/Program/utils_program.c \
	./src/Program/utils_program2.c \
	./src/Program/utils_program3.c \
	./src/Program/tests.c \
	./src/Program/prompt.c \
	./src/Lexer/lexer_lists_utils.c \
	./src/Lexer/lexer_word.c \
	./src/Lexer/lexer_utils.c \
	./src/Lexer/lexer.c \
	./src/Error_and_Utils/utils.c \
	./src/Error_and_Utils/errors.c \
	./src/Error_and_Utils/frees.c \
	./src/Error_and_Utils/utils2.c \
	./src/Error_and_Utils/utils3.c \
	./src/Expander/expander_dollar.c \
	./src/Expander/expander_quote.c \
	./src/Expander/expander_utils.c\
	./src/Expander/expander_utils2.c \
	./src/Parsing/Parser.c \
	./src/Parsing/Parsing_redirections.c \
	./src/Parsing/Redir_utils.c \
	./src/Parsing/Parsing_utils.c \
	./src/Parsing/Operateurs.c \
	./src/Parsing/Operateurs_Utils.c \
	./src/Parsing/Syntax_utils.c \
	./src/Parsing/Syntax.c \
	./src/Parsing/Quote.c \
	./src/Parsing/Utils_quote.c \
	./src/Builtins/builtin_env.c \
	./src/Builtins/builtin_echo.c \
	./src/Builtins/builtin_exit.c \
	./src/Builtins/builtin_export.c \
	./src/Builtins/builtin_unset.c \
	./src/Builtins/builtin_utils_unset.c \
	./src/Builtins/builtin_cd.c \
	./src/Builtins/builtin_utils.c \
	./src/Builtins/builtin_utils_export.c \
	./src/Builtins/builtin_export_addremove.c \
	./src/Builtins/cd_export.c \
	./src/Builtins_Awe/cd_comand.c \
	./src/Builtins_Awe/echo.c \
	./src/Builtins_Awe/env_concerns.c \
	./src/Builtins_Awe/exit.c \
	./src/Builtins_Awe/help_cmd_bis.c \
	./src/Builtins_Awe/export_cmd.c \
	./src/Builtins_Awe/help_cmd.c \
	./src/Builtins_Awe/local_cmd.c \
	./src/Builtins_Awe/shlvl.c \
	./src/Builtins_Awe/utils_thing.c \
	./src/Builtins_Awe/utils_built2.c \
	./src/Builtins_Awe/utils_built.c \
	./src/Exec/builtin_finder.c \
	./src/Exec/exec_builtins.c \
	./src/Exec/exec_end.c \
	./src/Exec/exec_utils.c \
	./src/Exec/exec_utils2.c \
	./src/Exec/fd_utils.c \
	./src/Exec/file_redirect.c \
	./src/Exec/pipe_manage.c \
	./src/Exec/process.c \
	./src/Here_Doc/here_doc.c \
	./src/Here_Doc/here_doc_utils.c \
	./src/Here_Doc/here_doc_utils2.c \
	./src/Here_Doc/here_doc_expand.c 

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


all : $(NAME)

clean :
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY	:		all clean fclean re