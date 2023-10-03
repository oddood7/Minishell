# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 15:58:12 by lde-mais          #+#    #+#              #
#    Updated: 2023/10/03 22:40:42 by lde-mais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 
LIBFT_PATH = include/libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC = ./src/Program/main.c \
	./src/Program/env.c \
	./src/Program/Signal.c \
	./src/Program/utils_program.c \
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
	./src/Parsing/Quote_utils.c \
	./src/Parsing/Quote.c \
	./src/Builtins/builtin_env.c \
	./src/Builtins/builtin_echo.c \
	./src/Builtins/builtin_exit.c \
	./src/Builtins/builtin_export.c \
	./src/Builtins/builtin_unset.c \
	./src/Builtins/builtin_cd.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


all : $(NAME)

clean :
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY	:		all clean fclean re