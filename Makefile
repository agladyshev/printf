# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stiffiny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/06 14:36:27 by stiffiny          #+#    #+#              #
#    Updated: 2021/06/28 17:34:22 by stiffiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

LIST		=	ft_printf.c

LIST_TEST	=	tests.c

LIBFT_DIR	=	./libft/

OBJS		= $(patsubst %.c,%.o,$(LIST))

OBJS_LIBFT	=	ft_putchar_fd.o ft_strlen.o ft_putstr_fd.o\
			ft_atoi.o ft_itoa.o ft_strchr.o \
			ft_strjoin.o ft_strdup.o ft_memset.o

OBJS_TEST	= $(patsubst %.c,%.o,$(LIST_TEST))

D_FILES		= $(wildcard *.d)

CC			= gcc

CFLAGS 		= -Wall -Wextra -Werror

RM			= rm -f

all	:		$(NAME)

$(NAME)	:	make-libft $(OBJS)
			ar rcs $(NAME) $(OBJS) $(addprefix $(LIBFT_DIR), $(OBJS_LIBFT))

.c.o :
	$(CC) $(CFLAGS) -I ./libft -c $< -o ${<:.c=.o} -MD

include	$(wildcard $(D_FILES))

make-libft	:
	$(MAKE) -C libft/

test	:	make-libft
	gcc *.c -I ./libft -L ./libft -lft -g -o test

bonus	:

clean-libft:
	$(MAKE) fclean -C libft/

clean	:	clean-libft
			$(RM) $(OBJS) $(OBJS_TEST) $(D_FILES)

fclean	:	clean
			$(RM) $(NAME) test

re	:		fclean all

.PHONY: all clean fclean re bonus test
