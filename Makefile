# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stiffiny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/06 14:36:27 by stiffiny          #+#    #+#              #
#    Updated: 2021/06/27 12:56:01 by stiffiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

LIST		=	ft_printf.c

LIST_TEST	=	tests.c

OBJS		= $(patsubst %.c,%.o,$(LIST))

OBJS_TEST	= $(patsubst %.c,%.o,$(LIST_TEST))

D_FILES		= $(wildcard *.d)

CC			= gcc

CFLAGS 		= -Wall -Wextra -Werror

RM			= rm -f

all	:		$(NAME)

$(NAME)	:	$(OBJS) make-libft
			ar rcs $(NAME) $(OBJS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} -MD

include	$(wildcard $(D_FILES))

make-libft:
	$(MAKE) -C libft/

test	:	$(OBJS) $(OBJS_TEST) make-libft
	gcc -Wall -Wextra -Werror $(OBJS) $(OBJS_TEST) -L ./libft -lft -o test

bonus	:

clean	:
			$(RM) $(OBJS) $(OBJS_TEST) $(D_FILES)

fclean	:	clean
			$(RM) $(NAME) test

re	:		fclean all

.PHONY: all clean fclean re bonus test
