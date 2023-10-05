# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 15:58:12 by lde-mais          #+#    #+#              #
#    Updated: 2023/10/06 00:09:54 by lde-mais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline -I/usr/local/opt/readline/include/readline
LIBFT_PATH = include/libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC = ./src/Program/main.c \
	./src/Program/env.c \
	./src/Program/Signal.c \
	./src/Program/utils_program.c \
	./src/Program/utils_program2.c \
	./src/Program/utils3.c \
	./src/Lexer/lexer_lists_utils.c \
	./src/Lexer/lexer_word.c \
	./src/Lexer/lexer.c \
	./src/Error_and_Utils/utils.c \
	./src/Error_and_Utils/errors.c \
	./src/Error_and_Utils/frees.c \
	./src/Error_and_Utils/utils2.c \
	./src/Expander/expander_dollar.c \
	./src/Expander/expander_quote.c \
	./src/Expander/expander_utils.c\
	./src/Expander/expander_utils2.c \
	./src/Parsing/Parser.c \
	./src/Parsing/Parsing_redirections.c \
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
	./src/Builtins/cd_export.c \
	./src/Exec/builtin_finder.c \
	./src/Exec/exec_builtins.c \
	./src/Exec/exec_end.c \
	./src/Exec/exec_utils.c \
	./src/Exec/exec_utils2.c \
	./src/Exec/fd_utils.c \
	./src/Exec/file_redirect.c \
	./src/Exec/pipe_manage.c \
	./src/Exec/process.c 

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)


all : $(NAME)

clean :
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY	:		all clean fclean re