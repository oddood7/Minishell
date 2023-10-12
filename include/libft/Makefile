# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asalic <asalic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 14:37:10 by asalic            #+#    #+#              #
#    Updated: 2023/10/12 17:02:20 by asalic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC	    	= gcc
CFLAGS		= -Wall -Wextra -Werror
PATHPRINTF	= libftprintf/libftprintf.a
INCLUDE		= libftprintf/libftprintf.h libft.h

SRCS    =     ft_isalpha.c \
            ft_isdigit.c \
            ft_isalnum.c \
            ft_isascii.c \
            ft_isprint.c \
            ft_strlen.c \
            ft_memset.c \
            ft_bzero.c \
            ft_memcpy.c \
            ft_memmove.c \
            ft_strlcpy.c \
            ft_strlcat.c \
            ft_toupper.c \
            ft_tolower.c \
            ft_strchr.c \
            ft_strrchr.c \
            ft_strncmp.c \
            ft_memchr.c \
            ft_memcmp.c \
            ft_strnstr.c \
            ft_atoi.c \
            ft_calloc.c \
            ft_strdup.c \
            ft_substr.c \
            ft_strjoin.c \
            ft_split.c \
            ft_strmapi.c \
            ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strtrim.c \
			ft_itoa.c

OBJS    =    ${SRCS:.c=.o}

BONUS_SRCS    =    ft_lstnew.c \
                ft_lstadd_front.c \
                ft_lstsize.c \
                ft_lstlast.c \
                ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c 

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

.c.o :
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -Llibftprintf -lftprintf -Llibft -lft

all : ${PATHPRINTF} ${NAME} ${INCLUDE}

$(NAME): ${PATHPRINTF} ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

${PATHPRINTF} :
	@make -s -C libftprintf

clean :
	@rm -rf ${OBJS} ${BONUS_OBJS}
	@make -s clean -C libftprintf

fclean : clean
	@rm -f ${NAME}
	@make -s fclean -C libftprintf

re : fclean all

rebonus : fclean bonus

bonus : ${OBJS} ${BONUS_OBJS}
	@ar rc ${NAME} ${OBJS} ${BONUS_OBJS}
	@ranlib ${NAME}

.PHONY:	all clean fclean re bonus rebonus
