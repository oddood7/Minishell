# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asalic <asalic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 15:58:12 by lde-mais          #+#    #+#              #
#    Updated: 2023/10/17 15:30:29 by asalic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS 		= -Wall -Wextra -Werror -g3
INCLUDE 	= include/libft/libft.h include/libft/libftprintf/libftprintf.h \
				include/minishell.h
LIBFT_PATH 	= include/libft/libft.a
LIBFT 		= include/libft
LIBS 		= -lreadline -Linclude/libft -lft \
				-Linclude/libft/libftprintf -lftprintf

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
	./src/Error_and_Utils/garbage.c \
	./src/Error_and_Utils/errors.c \
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
	./src/Builtins_Awe/cd_comand.c \
	./src/Builtins_Awe/echo.c \
	./src/Builtins_Awe/env_concerns.c \
	./src/Builtins_Awe/exit.c \
	./src/Builtins_Awe/export_cmd.c \
	./src/Builtins_Awe/local_cmd.c \
	./src/Builtins_Awe/shlvl.c \
	./src/Builtins_Awe/utils_built2.c \
	./src/Builtins_Awe/utils_built.c \
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

RED		= \033[1;31m
GREEN	= \033[1;32m
NO_CLRS	= \033[0m

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

all : $(LIBFT_PATH) $(NAME) $(INCLUDE)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)/src/Builtins
	@mkdir -p $(OBJ_DIR)/src/Builtins_Awe
	@mkdir -p $(OBJ_DIR)/src/Error_and_Utils
	@mkdir -p $(OBJ_DIR)/src/Exec
	@mkdir -p $(OBJ_DIR)/src/Expander
	@mkdir -p $(OBJ_DIR)/src/Here_Doc
	@mkdir -p $(OBJ_DIR)/src/Lexer
	@mkdir -p $(OBJ_DIR)/src/Parsing
	@mkdir -p $(OBJ_DIR)/src/Program
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@echo "\n$(GREEN)>----Compilation Minishell Done----<$(NO_CLRS)\n"

$(LIBFT_PATH) :
	@make -s -C $(LIBFT)

clean :
	@rm -rf $(OBJ_DIR) $(OBJ)
	@make -s clean -C $(LIBFT)
	@echo "\n$(RED)>> Clean Done <<$(NO_CLRS)"

fclean : clean
	@rm -f $(NAME)
	@make -s fclean -C $(LIBFT)
	@echo "$(RED)>> Fclean Done <<$(NO_CLRS)\n"

re : fclean all
	@make -s all

.PHONY	:		all clean fclean re