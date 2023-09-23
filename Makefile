# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 15:58:12 by lde-mais          #+#    #+#              #
#    Updated: 2023/09/22 15:58:20 by lde-mais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 13:28:10 by nassm             #+#    #+#              #
#    Updated: 2023/09/16 18:26:06 by lde-mais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -I/usr/local/opt/readline/include
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC = ./src/main.c \
	./src/check_str_synthax.c \
	./src/parsing.c \
	./src/execute.c \
	./src/execute_core.c \
	./src/arg_split.c \
	./src/free.c \
	./src/quote.c \
	./src/check_spe_character.c \
	./src/exit_synthax_error.c \
	./src/token.c \
	./src/wait_for_pids.c \
	./src/create_t_env.c \
	./src/is_in_quote.c \
	./src/handle_dollar.c \
	./src/handle_dollar_utils.c \
	./src/join_quote.c \
	./src/check_tok.c \
	./src/get_cmd.c \
	./src/close.c \
	./src/prepare_fd.c \
	./src/execute_core_utils.c \
	./src/here_doc.c \
	./src/handle_redirin.c \
	./src/a_exit.c \
	./src/a_echo.c \
	./src/a_env.c \
	./src/a_pwd.c \
	./src/a_cd.c \
	./src/a_unset.c \
	./src/create_var.c \
	./src/a_export.c \
	./src/a_export_utils.c \
	./src/a_export_utils_bis.c \
	./src/signal.c \

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -I/usr/local/opt/readline/include


all : $(NAME)

clean :
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY	:		all clean fclean re